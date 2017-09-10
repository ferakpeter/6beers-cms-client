type actions =
  /* route Actions */
  | Brewery
  | Beer
  | Order
  | Contact
  | All
  /* external API calls */
  | SetAvailableBeers (list Beer.beer)
  | SetNews (list Teaser.news);

type state = {
  availableBeers: list Beer.beer,
  selectedBeers: list Beer.beer,
  shoppingCart: list Beer.beer,
  news: list Teaser.news,
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
  caption: option string
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
    { availableBeers: [ ], selectedBeers: [ ], shoppingCart: [ ], news: [ ], selectedRoute: All}
  },
  reducer: fun action state => {
    switch action {
      /* router actions */
      | All => ReasonReact.Update {...state, selectedRoute: All}
      | Brewery => ReasonReact.Update {...state, selectedRoute: Brewery}
      | Beer => ReasonReact.Update {...state, selectedRoute: Beer}
      | Order => ReasonReact.Update {...state, selectedRoute: Order}
      | Contact => ReasonReact.Update {...state, selectedRoute: Contact}
      /* Api actions */
      | SetAvailableBeers beers => ReasonReact.Update {...state, availableBeers: beers }
      | SetNews news => ReasonReact.Update {...state, news: news };
    }
  },
  didMount: fun {reduce} => {

    let parseConfig = fun (json:Js.Json.t) => {

      /* Js.log "received json";
      Js.log json; */

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
          caption: jsonValue |> optional (field "caption" string)
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

      let apiRespone = root json;
      /* Js.log "json response decoded"; */
      apiRespone;
    };

    let removeEmpty = fun listOfString => List.filter (fun s => s != "") listOfString;

    let mapJsonValuesToState (cmsContent:cmsNewsList) : unit => {
      /* Js.log cmsContent; */
      let headlines = List.map (fun item => item.headline) cmsContent.response;
      /* Js.log headlines; */
      let beercodes =
        List.map (fun (item:string) => switch (Js.Re.exec item (Js.Re.fromString "beer-(\w+).*")) {
          | None => "";
          | Some match =>
            let test = Array.length (Js.Re.matches match) <= 2 ? Array.get (Js.Re.matches match) 1 : "";
            test;
        }) headlines |> removeEmpty |> List.sort_uniq compare;

      /* Js.log beercodes; */

      let beers = beercodes |> List.map (fun beercode => {

        /* Js.log beercode; */
        let beerInfo : cmsNewsItem = List.find (fun item => item.headline == (String.concat "" [ "beer-", beercode ])) cmsContent.response;
        Js.log (String.concat " " [ "beerInfo", beerInfo.headline ]);
        let beerDetail : cmsNewsItem = List.find (fun item => item.headline == (String.concat "" [ "beer-", beercode, "-detail" ])) cmsContent.response;
        Js.log (String.concat " " [ "beerDetail", beerDetail.headline ]);

        /* Js.log beerInfo;
        Js.log beerDetail; */

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

      reduce (fun _ => SetAvailableBeers (beers |> List.filter (fun (item:Beer.beer) => (item.quantityLarge + item.quantitySmall) > 0) |> List.sort (fun (a:Beer.beer) (b:Beer.beer) => a.id - b.id) )) ();

      let cmsNews =  cmsContent.response |> List.filter (fun cmsItem => Js.Re.test cmsItem.headline (Js.Re.fromString "news-.*"));

      Js.log cmsNews;

      let news = cmsNews |> List.map (fun (n:cmsNewsItem) => {
        let mappedItem : Teaser.news = {
          id: n.headline,
          title: n.subheadline,
          imageLink: String.concat "" [ "http://www.6beers.at/cms/", n.picture.img.src ],
          link: n.picture.caption,
          content: n.teaser
        };
        mappedItem;
      });

      reduce (fun _ => SetNews news) ();

      ()
    };

    Js.Promise.(
      Bs_fetch.fetch "http://www.6beers.at/cms/index.php/api.html?modul=NewsList&limit=1000"
        |> then_ Bs_fetch.Response.json
        |> then_ (fun result => { parseConfig result
        |> mapJsonValuesToState
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
                <Teaser news=state.news />
                <br />

                <hr> </hr>
                <div className="row">
                  <img className="img-responsive center-block" src="assets/img/logo.png" style=(ReactDOMRe.Style.make height::"100px" ()) />
                </div>

                <Brewery />

                <hr> </hr>
                <div className="row">
                  <img className="img-responsive center-block" src="assets/img/logo.png" style=(ReactDOMRe.Style.make height::"100px" ()) />
                </div>

                <BeerDescription />

                <h2> (ReasonReact.stringToElement "Available Beers") </h2>
                (ReasonReact.arrayToElement (Array.of_list beers))

                <hr> </hr>
                <div className="row">
                  <img className="img-responsive center-block" src="assets/img/logo.png" style=(ReactDOMRe.Style.make height::"100px" ()) />
                </div>

                <Contact />

                <Footer />
              </div>

            | Beer => <BeerDescription />
            | Brewery => <Brewery />
            | Order => <div> (ReasonReact.arrayToElement (Array.of_list beers)) </div>
            | Contact => <Contact />
            /* Do nothing for non route actions */
            | SetAvailableBeers beers => <div onClick=(fun _ => Js.log beers)>  </div>
            | SetNews news => <div onClick=(fun _ => Js.log news)>  </div>
          })
      </div>

    </div>
  }
};
