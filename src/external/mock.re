let newsMock : Teaser.news = {
    id: "1",
    title: "Test",
    imageLink: "",
    link: Some "test",
    content: "Lorem Ipsum."
  };

let beerMock : Beer.beer = {
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
    glassImageLink: "string",
    labelImageLink: "",
    maltinessRating: 1,
    hoppinessRating: 3,
    bitternessRating: 4,
    inShoppingCart: false
  };

let apiItems : Api.apiItems = {
    news: [ newsMock ],
    beers: [ beerMock ]
  };