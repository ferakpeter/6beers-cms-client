type actions =
  /* route Actions */
  | Brewery
  | Beer
  | Order
  | Contact
  | All
  /* external API calls */
  | FetchCmsApi (list Beer.beer);

type state = {
  availableBeers: list Beer.beer,
  selectedBeers: list Beer.beer,
  shoppingCart: list Beer.beer,
  selectedRoute: actions
};

type cmsBeerSubheadline = {
  name: string,
  id: int
};

type cmsBeerDetailSubheadline = {
  priceSmall: float,
  priceLarge: float,
  quantitySmall: int,
  quantityLarge: int
};

type cmsImg = {
  src: string,
  width: int,
  height: int
};

type cmsPicture = {
  id: string,
  img: cmsImg,
  caption: string
};

type cmsNewsItem = {
  id: string,
  headline: string,
  subheadline: string,
  teaser: string,
  picture: cmsPicture
};

type cmsNewsList = {
  response: list cmsNewsItem,
  status: string
};

let click _event _self => Js.log "clicked!";

let component = ReasonReact.reducerComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {
    { availableBeers: [ ], selectedBeers: [ ], shoppingCart: [ ], selectedRoute: All}
  },
  reducer: fun action state => {
    switch action {
      /* router actions */
      | All => ReasonReact.Update {...state, selectedRoute: All}
      | Brewery => ReasonReact.Update {...state, selectedRoute: Brewery}
      | Beer => ReasonReact.Update {...state, selectedRoute: Beer}
      | Order => ReasonReact.Update {...state, selectedRoute: Order}
      | Contact => ReasonReact.Update {...state, selectedRoute: Contact}

      | FetchCmsApi beers => ReasonReact.Update {...state, availableBeers: beers };
    }
  },
  didMount: fun {reduce} => {

    let parseConfig = fun (json:Js.Json.t) => {

      Js.log "received json";
      Js.log json;

      let img (jsonValue:Js.Json.t) : cmsImg =>
        Json.Decode.{
          src: jsonValue |> field "src" string,
          width: jsonValue |> field "width" int,
          height: jsonValue |> field "height" int
        };

      let picture (jsonValue:Js.Json.t) : cmsPicture =>
        Json.Decode.{
          id: jsonValue |> field "id" string,
          img: jsonValue |> field "img" img,
          caption: jsonValue |> field "caption" string
        };

      let newsItem (jsonValue:Js.Json.t) : cmsNewsItem =>
        Json.Decode.{
          id: jsonValue |> field "id" string,
          headline: jsonValue |> field "headline" string,
          subheadline: jsonValue |> field "subheadline" string,
          teaser: jsonValue |> field "teaser" string,
          picture: jsonValue |> field "picture" picture
        };

      let newsItems (jsonValue:Js.Json.t) : list cmsNewsItem => Json.Decode.(list newsItem jsonValue);

      let newsList (jsonValue:Js.Json.t) : cmsNewsList =>
        Json.Decode.{
          response: jsonValue |> field "response" newsItems,
          status: jsonValue |> field "status" string
        };

      let root (jsonValue:Js.Json.t) => newsList jsonValue;

      root json;


    };

    let mapJsonValuesToBeer (cmsContent:cmsNewsList) : (list Beer.beer) => {


      Js.log cmsContent;
      let headlines = List.map (fun item => item.headline) cmsContent.response;
      /* Js.log headlines; */
      let beercodes =
        List.map (fun (item:string) => switch (Js.Re.exec item (Js.Re.fromString "beer-(\w+).*")) {
          | None => "";
          | Some match =>
            let test = Array.length (Js.Re.matches match) <= 2 ? Array.get (Js.Re.matches match) 1 : "";
            test;
        }) headlines |> List.sort_uniq compare;

      beercodes |> List.map (fun beercode => {

        let beerInfo : cmsNewsItem = List.find (fun item => Js.Re.test item.headline (Js.Re.fromString (String.concat "" [ "beer-", beercode ]))) cmsContent.response;
        let beerDetail : cmsNewsItem = List.find (fun item => Js.Re.test item.headline (Js.Re.fromString (String.concat "" [ "beer-", beercode, "-detail" ]))) cmsContent.response;

        let parseBeerSubheadline value : cmsBeerSubheadline => {
          let parsedMatch = Js.Re.exec value (Js.Re.fromString "(.+)\/(.+)");
          switch (parsedMatch) {
            | None => { name: "", id: 0 };
            | Some match =>
              { name: Array.get (Js.Re.matches match) 1, id: int_of_string (Array.get (Js.Re.matches match) 2) };
          }
        };

        let parseBeerDetailSubheadline value : cmsBeerDetailSubheadline => {
          let parsedMatch = Js.Re.exec value (Js.Re.fromString "(.+)\/(.+)\/(.+)\/(.+)");
          switch (parsedMatch) {
            | None => { priceSmall: 0.0, priceLarge: 0.0, quantitySmall: 0, quantityLarge: 0 };
            | Some match =>
              { priceSmall: float_of_string (Array.get (Js.Re.matches match) 1), priceLarge: float_of_string (Array.get (Js.Re.matches match) 2), quantitySmall: int_of_string (Array.get (Js.Re.matches match) 3), quantityLarge: int_of_string (Array.get (Js.Re.matches match) 4) };
          }
        };

        let beerSubheadline = parseBeerSubheadline beerInfo.subheadline;
        let beerDetailSubheadline = parseBeerDetailSubheadline beerDetail.subheadline;

        let result : Beer.beer = {
          id: beerSubheadline.id,
          code: beercode,
          name: beerSubheadline.name,
          description: beerInfo.teaser,
          detail: beerDetail.teaser,
          priceSmall: beerDetailSubheadline.priceSmall,
          priceLarge: beerDetailSubheadline.priceLarge,
          quantitySmall: beerDetailSubheadline.quantitySmall,
          quantityLarge: beerDetailSubheadline.quantityLarge,
          bottleImageLink: String.concat "" [ "http://www.6beers.at/cms/", beerInfo.picture.img.src ],
          glassImageLink: "",
          labelImageLink: String.concat "" [ "http://www.6beers.at/cms/", beerDetail.picture.img.src] };
          result;
      });
    };

    let changeState (beers:list Beer.beer) => reduce (fun _ => FetchCmsApi beers) ();

    Js.Promise.(
      Bs_fetch.fetch "http://www.6beers.at/cms/index.php/api.html?modul=NewsList"
        |> then_ Bs_fetch.Response.json
        |> then_ (fun result => { parseConfig result
        |> mapJsonValuesToBeer
        |> List.filter (fun (item:Beer.beer) => (item.quantityLarge + item.quantitySmall) > 0)
        |> changeState
        |> resolve })
    );

    let router =
      DirectorRe.makeRouter {
        "/": reduce (fun _ => All),
        "/beer": reduce (fun _ => Beer),
        "/brewery": reduce (fun _ => Brewery),
        "/contact": reduce (fun _ => Contact),
        "/order": reduce (fun _ => Order)
      };
    DirectorRe.init router "/";

    ReasonReact.NoUpdate;
  },
  render: fun {state, update} => {
    let beers = List.map (fun (b:Beer.beer) => <Beer beer=b key=b.code /> ) state.availableBeers;

    <div className="App">

      <Header />

      <div className="wrapper">

      (switch (state.selectedRoute)
          {
            | All => <div>
                <Teaser />

                <div className="row">
                  <img className="img-responsive center-block" src="assets/img/logo.png" style=(ReactDOMRe.Style.make height::"100px" ()) />
                </div>

                <Brewery />

                <div className="row">
                  <img className="img-responsive center-block" src="assets/img/logo.png" style=(ReactDOMRe.Style.make height::"100px" ()) />
                </div>

                <BeerDescription />

                (ReasonReact.arrayToElement (Array.of_list beers))

                <div className="row">
                  <img className="img-responsive center-block" src="assets/img/logo.png" style=(ReactDOMRe.Style.make height::"100px" ()) />
                </div>

                <Contact />
              </div>
            | Beer => <BeerDescription />
            | Brewery => <Brewery />
            | Order => <div> (ReasonReact.arrayToElement (Array.of_list beers)) </div>
            | Contact => <Contact />
          })
      </div>

      <Footer />

    </div>
  }
};
