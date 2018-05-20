let cmsUrl = "https://www.6beers.at/cms/";

let absolutePath = relativePath => String.concat("", [cmsUrl, relativePath]);

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
  bitternessRating: int,
};

type cmsImg = {
  src: string,
  width: int,
  height: int,
};

type cmsPicture = {
  id: string,
  img: cmsImg,
  caption: option(string),
};

type cmsNewsItem = {
  id: string,
  headline: string,
  subheadline: string,
  teaser: string,
  picture: cmsPicture,
};

type cmsNewsList = {
  response: list(cmsNewsItem),
  status: string,
};

type apiItems = {
  news: list(Teaser.news),
  beers: list(Beer.beer),
};

module Decode = {
  let img = (jsonValue: Js.Json.t) =>
    Json.Decode.{
      src: jsonValue |> field("src", string),
      width: jsonValue |> field("width", int),
      height: jsonValue |> field("height", int),
    };
  let picture = (jsonValue: Js.Json.t) =>
    Json.Decode.{
      id: jsonValue |> field("id", string),
      img: jsonValue |> field("img", img),
      caption: jsonValue |> optional(field("caption", string)),
    };
  let newsItem = (jsonValue: Js.Json.t) =>
    Json.Decode.{
      id: jsonValue |> field("id", string),
      headline: jsonValue |> field("headline", string),
      subheadline: jsonValue |> field("subheadline", string),
      teaser: jsonValue |> field("teaser", string),
      picture: jsonValue |> field("picture", picture),
    };
  let newsList = (jsonValue: Js.Json.t) =>
    Json.Decode.{
      response: jsonValue |> field("response", list(newsItem)),
      status: jsonValue |> field("status", string),
    };
};

let parseConfig = (json: Js.Json.t) => {
  let apiRespone = Decode.newsList(json);
  /* Js.log "json response decoded"; */
  apiRespone;
};

let removeEmpty = listOfString => List.filter(s => s != "", listOfString);

let mapJsonValuesToState = (cmsContent: cmsNewsList) : apiItems => {
  /* Js.log cmsContent; */
  let headlines = List.map(item => item.headline, cmsContent.response);
  /* Js.log headlines; */
  let beercodes =
    List.map(
      (item: string) =>
        switch (Js.Re.exec(item, Js.Re.fromString("beer-(\\w+).*"))) {
        | None => ""
        | Some(match) =>
          let test =
            Array.length(Js.Re.matches(match)) <= 2 ?
              Js.Re.matches(match)[1] : "";
          test;
        },
      headlines,
    )
    |> removeEmpty
    |> List.sort_uniq(compare);
  /* Js.log beercodes; */
  let beers =
    beercodes
    |> List.map(beercode => {
         /* Js.log beercode; */
         let beerInfo: cmsNewsItem =
           List.find(
             item => item.headline == String.concat("", ["beer-", beercode]),
             cmsContent.response,
           );
         Js.log(String.concat(" ", ["beerInfo", beerInfo.headline]));
         let beerDetail: cmsNewsItem =
           List.find(
             item =>
               item.headline
               == String.concat("", ["beer-", beercode, "-detail"]),
             cmsContent.response,
           );
         Js.log(String.concat(" ", ["beerDetail", beerDetail.headline]));
         /* Js.log beerInfo;
            Js.log beerDetail; */
         let parseBeerSubheadline = value => {
           let parsedMatch =
             Js.Re.exec(value, Js.Re.fromString("(.+)\\/(.+)\\/(.+)"));
           switch (parsedMatch) {
           | None => {name: "", id: 0, sort: ""}
           | Some(match) => {
               name: Js.Re.matches(match)[1],
               id: int_of_string(Js.Re.matches(match)[2]),
               sort: Js.Re.matches(match)[3],
             }
           };
         };
         let parseBeerDetailSubheadline = value => {
           let parsedMatch =
             Js.Re.exec(
               value,
               Js.Re.fromString(
                 "(.+)\\/(.+)\\/(.+)\\/(.+)\\/(.+)\\/(.+)\\/(.+)",
               ),
             );
           switch (parsedMatch) {
           | None => {
               priceSmall: 0.0,
               priceLarge: 0.0,
               quantitySmall: 0,
               quantityLarge: 0,
               maltinessRating: 0,
               hoppinessRating: 0,
               bitternessRating: 0,
             }
           | Some(match) => {
               priceSmall: float_of_string(Js.Re.matches(match)[1]),
               priceLarge: float_of_string(Js.Re.matches(match)[2]),
               quantitySmall: int_of_string(Js.Re.matches(match)[3]),
               quantityLarge: int_of_string(Js.Re.matches(match)[4]),
               maltinessRating: int_of_string(Js.Re.matches(match)[5]),
               hoppinessRating: int_of_string(Js.Re.matches(match)[6]),
               bitternessRating: int_of_string(Js.Re.matches(match)[7]),
             }
           };
         };
         let beerSubheadline = parseBeerSubheadline(beerInfo.subheadline);
         let beerDetailSubheadline =
           parseBeerDetailSubheadline(beerDetail.subheadline);
         let result: Beer.beer = {
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
           bottle: {
             thumbnail:
               Thumbnail(
                 Some(absolutePath(beerInfo.picture.img.src)),
                 Some(250),
               ),
             fullsize:
               Fullsize(
                 Some(absolutePath(beerInfo.picture.img.src)),
                 Some(350),
               ),
           },
           glass: {
             thumbnail: Thumbnail(None, Some(350)),
             fullsize: Fullsize(None, Some(500)),
           },
           label: {
             thumbnail:
               Thumbnail(
                 Some(absolutePath(beerDetail.picture.img.src)),
                 Some(200),
               ),
             fullsize:
               Fullsize(
                 Some(absolutePath(beerDetail.picture.img.src)),
                 Some(400),
               ),
           },
           ratings: [|
             Maltiness("maltiness", beerDetailSubheadline.maltinessRating),
             Hoppiness("hoppiness", beerDetailSubheadline.hoppinessRating),
             Bitterness("bitterness", beerDetailSubheadline.bitternessRating),
           |],
         };
         result;
       });
  let cmsNews =
    cmsContent.response
    |> List.filter(cmsItem =>
         Js.Re.test(cmsItem.headline, Js.Re.fromString("news-.*"))
       );
  let news =
    cmsNews
    |> List.map((n: cmsNewsItem) => {
         let mappedItem: Teaser.news = {
           id: n.headline,
           title: n.subheadline,
           imageLink: absolutePath(n.picture.img.src),
           link: n.picture.caption,
           content: n.teaser,
         };
         mappedItem;
       });
  let filterAndSortBeers = beers =>
    beers
    |> List.filter((item: Beer.beer) =>
         item.quantityLarge + item.quantitySmall > 0
       )
    |> List.sort((a: Beer.beer, b: Beer.beer) => a.id - b.id);
  {news, beers: beers |> filterAndSortBeers};
};