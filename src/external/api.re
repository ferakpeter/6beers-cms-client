type cmsBeerSubheadline = {
  name: string,
  id: int,
  sort: string,
};

type cmsBeerDetailSubheadline = {
  priceSmall: float,
  priceLarge: float,
  quantitySmall: int,
  quantityLarge: int,
  maltinessRating: int,
  hoppinessRating: int,
  bitternessRating: int
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

type apiItems = {
  news: list Teaser.news,
  beers: list Beer.beer
};

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

let mapJsonValuesToState = fun (cmsContent:cmsNewsList) : apiItems => {
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
      let parsedMatch = Js.Re.exec value (Js.Re.fromString "(.+)\/(.+)\/(.+)");
      switch (parsedMatch) {
        | None => { name: "", id: 0, sort: ""};
        | Some match =>
          { name: Array.get (Js.Re.matches match) 1, id: int_of_string (Array.get (Js.Re.matches match) 2), sort: (Array.get (Js.Re.matches match) 3) };
      }
    };

    let parseBeerDetailSubheadline value : cmsBeerDetailSubheadline => {
      let parsedMatch = Js.Re.exec value (Js.Re.fromString "(.+)\/(.+)\/(.+)\/(.+)\/(.+)\/(.+)\/(.+)");
      switch (parsedMatch) {
        | None => { priceSmall: 0.0, priceLarge: 0.0, quantitySmall: 0, quantityLarge: 0, maltinessRating: 0, hoppinessRating: 0, bitternessRating: 0 };
        | Some match =>
          { priceSmall: float_of_string (Array.get (Js.Re.matches match) 1), priceLarge: float_of_string (Array.get (Js.Re.matches match) 2), quantitySmall: int_of_string (Array.get (Js.Re.matches match) 3), quantityLarge: int_of_string (Array.get (Js.Re.matches match) 4), maltinessRating: int_of_string (Array.get (Js.Re.matches match) 5), hoppinessRating: int_of_string (Array.get (Js.Re.matches match) 6), bitternessRating: int_of_string (Array.get (Js.Re.matches match) 7) };
      }
    };

        let beerSubheadline = parseBeerSubheadline beerInfo.subheadline;
        let beerDetailSubheadline = parseBeerDetailSubheadline beerDetail.subheadline;

        let result : Beer.beer = {
          id: beerSubheadline.id,
          code: beercode,
          name: beerSubheadline.name,
          sort: beerSubheadline.sort,
          description: beerInfo.teaser,
          detail: beerDetail.teaser,
          priceSmall: beerDetailSubheadline.priceSmall,
          priceLarge: beerDetailSubheadline.priceLarge,
          quantitySmall: beerDetailSubheadline.quantitySmall,
          quantityLarge: beerDetailSubheadline.quantityLarge,
          bottleImageLink: Cms.absolutePath beerInfo.picture.img.src,
          glassImageLink: "",
          labelImageLink: Cms.absolutePath beerDetail.picture.img.src,
          maltinessRating: beerDetailSubheadline.maltinessRating,
          hoppinessRating: beerDetailSubheadline.hoppinessRating,
          bitternessRating: beerDetailSubheadline.bitternessRating };

        result;
      });

      let cmsNews =  cmsContent.response |> List.filter (fun cmsItem => Js.Re.test cmsItem.headline (Js.Re.fromString "news-.*"));

      let news = cmsNews |> List.map (fun (n:cmsNewsItem) => {
        let mappedItem : Teaser.news = {
          id: n.headline,
          title: n.subheadline,
          imageLink: Cms.absolutePath n.picture.img.src,
          link: n.picture.caption,
          content: n.teaser
        };
        mappedItem;
      });

      let filterAndSortBeers beers => beers
        |> List.filter (fun (item:Beer.beer) => (item.quantityLarge + item.quantitySmall) > 0)
        |> List.sort (fun (a:Beer.beer) (b:Beer.beer) => a.id - b.id);

      {
        news: news,
        beers: (beers |>  filterAndSortBeers)
      };
    };
