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
  bottleImageLink: "string",
  bottleImageHeightSmall: Some(350),
  bottleImageHeightLarge: Some(500),
  glassImageLink: "string",
  glassImageHeightSmall: Some(350),
  glassImageHeightLarge: Some(500),
  labelImageLink: "",
  labelImageHeightSmall: Some(200),
  labelImageHeightLarge: Some(400),
  maltinessRating: 1,
  hoppinessRating: 3,
  bitternessRating: 4,
  inShoppingCart: false,
};

let apiItems: Api.apiItems = {news: [newsMock], beers: [beerMock]};
