let newsMock: Teaser.news = {
  id: "1",
  title: "Test",
  imageLink: "",
  link: Some("test"),
  content: "Lorem Ipsum.",
};

let beerMock: Beer.beer = {
  id: 1,
  code: "test",
  name: "Test",
  sort: "Pale Ale",
  description: "This is A TEST",
  detail: "Lorem Ipsum",
  priceSmall: 3.0,
  priceLarge: 4.5,
  quantitySmall: 100,
  quantityLarge: 100,
  bottle: {
    thumbnail: Thumbnail(Some("string"), Some(350)),
    fullsize: Fullsize(Some("string"), Some(500))
  },
  glass: {
    thumbnail: Thumbnail(Some("string"), Some(350)),
    fullsize: Fullsize(Some("string"), Some(500))
  },
  label: {
    thumbnail: Thumbnail(Some("string"), Some(200)),
    fullsize: Fullsize(Some("string"), Some(400))
  },
  ratings: [|
    Maltiness("maltiness", 1),
    Hoppiness("hoppiness", 3),
    Bitterness("bitterness", 4)
  |]
};

let apiItems: Api.apiItems = {news: [newsMock], beers: [beerMock]};
