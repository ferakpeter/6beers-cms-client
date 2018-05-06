type routes =
  | Brewery
  | Beer(option(int))
  | AboutUs
  | Contact
  | All;

let urlToSelectedRoute = hash =>
  switch (hash) {
  | "beer" => Beer(None)
  | "brewery" => Brewery
  | "contact" => Contact
  | "aboutus" => AboutUs
  | _ => All
  };

type actions =
  /* route Actions */
  | Navigate(routes)
  /* User actions */
  | AddBeerToShoppingCart(string)
  /* external API calls */
  | LoadApi
  | ApiCallFailed
  | UpdateUi(list(Beer.beer), list(Teaser.news))
  | IncreaseBottleImage(int)
  | DecreaseBottleImage(int);

type apiStatus =
  | Loading
  | Loaded
  | Failed;

type state = {
  availableBeers: list(Beer.beer),
  selectedBeer: option(Beer.beer),
  shoppingCart: list(string),
  news: list(Teaser.news),
  selectedRoute: routes,
  apiStatus,
};

let namespace = "6beers-client-app";

[@bs.val] external unsafeJsonParse : string => 'a = "JSON.parse";

let saveLocally = (shoppingCart: list(string)) =>
  switch (Js.Json.stringifyAny(shoppingCart)) {
  | None => ()
  | Some(stringifiedShoppingCart) =>
    try (
      Dom.Storage.(
        localStorage |> setItem(namespace, stringifiedShoppingCart)
      )
    ) {
    | exn => Js.log("no local storage available in this browser")
    }
  };

let addBeerToShoppingCart = (beerCode, _event) =>
  AddBeerToShoppingCart(beerCode);

let navigateToBeer = (send, name, _event, beerId) =>
  send(Navigate(Beer(beerId)));

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    let items =
      try (Dom.Storage.(localStorage |> getItem(namespace))) {
      | exn =>
        Js.log("local storage not available in this browser");
        None;
      };
    let shoppingCartBeerCodes =
      switch (items) {
      | None => []
      | Some(shoppingCart) => unsafeJsonParse(shoppingCart)
      };
    {
      availableBeers: [],
      selectedBeer: None,
      shoppingCart: shoppingCartBeerCodes,
      news: [],
      selectedRoute:
        urlToSelectedRoute(
          ReasonReact.Router.dangerouslyGetInitialUrl().hash,
        ),
      apiStatus: Loading,
    };
  },
  reducer: (action, state) =>
    switch (action) {
    /* router actions */
    | Navigate(page) => ReasonReact.Update({...state, selectedRoute: page})
    /* User Actions */
    | AddBeerToShoppingCart(beer) =>
      let shoppingCart = List.append(state.shoppingCart, [beer]);
      Js.log(shoppingCart);
      ReasonReact.UpdateWithSideEffects(
        {...state, shoppingCart},
        (_self => saveLocally(shoppingCart)),
      );
    /* Api actions */
    | LoadApi =>
      ReasonReact.UpdateWithSideEffects(
        {...state, apiStatus: Loading},
        (
          self =>
            Js.Promise.(
              Fetch.fetch(
                Cms.absolutePath(
                  "index.php/api.html?modul=NewsList&limit=1000",
                ),
              )
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> Api.parseConfig
                   |> Api.mapJsonValuesToState
                   |> (
                     items => self.send(UpdateUi(items.beers, items.news))
                   )
                   |> resolve
                 )
              |> catch(_err => Js.Promise.resolve(self.send(ApiCallFailed)))
              |> ignore
            )
        ),
      )
    | ApiCallFailed => ReasonReact.Update({...state, apiStatus: Failed})
    | UpdateUi(beers, news) =>
      ReasonReact.Update({
        ...state,
        apiStatus: Loaded,
        availableBeers: beers,
        news,
      })
    | IncreaseBottleImage(beerId) =>
      ReasonReact.Update({...state, availableBeers: state.availableBeers})
    | DecreaseBottleImage(beerId) =>
      ReasonReact.Update({...state, availableBeers: state.availableBeers})
    },
  didMount: self => {
    self.send(LoadApi);
    ReasonReact.NoUpdate;
  },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          self.send(Navigate(urlToSelectedRoute(url.hash)))
        ),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
  render: ({state, send}) => {
    let beers =
      List.map(
        (b: Beer.beer) =>
          <Beer
            beer=(Detail(b))
            key=b.code
            onOrdered=(_event => send(AddBeerToShoppingCart(b.code)))
          />,
        state.availableBeers,
      );
    <div className="App">
      <Header />
      (
        switch (state.selectedRoute) {
        | All =>
          <div>
            <div>
              <div className="section margin-top-l" id="selection-container">
                <div className="container">
                  <Selection
                    beers=(List.map(beer => beer, state.availableBeers))
                    onClicked=(code => send(AddBeerToShoppingCart(code)))
                  />
                </div>
              </div>
              <HorizontalSeparator />
              <Brewery />
              <HorizontalSeparator />
              <Teaser news=state.news />
              <HorizontalSeparator />
              <AboutUs />
              <HorizontalSeparator />
              <Contact />
              <Logo height="200px" inverseColors=false />
            </div>
            <Footer />
          </div>
        | Beer(beerId) =>
          <div className="section" id="beer">
            <div className="container">
              <h2> (ReasonReact.stringToElement("Beer")) </h2>
              (
                switch (beerId) {
                | None =>
                  <div>
                    (ReasonReact.arrayToElement(Array.of_list(beers)))
                  </div>
                | Some(id) =>
                  let b: Beer.beer =
                    List.find(
                      (beer: Beer.beer) => beer.id == id,
                      state.availableBeers,
                    );
                  <Beer
                    beer=(Detail(b))
                    key=b.code
                    onOrdered=(_event => send(AddBeerToShoppingCart(b.code)))
                  />;
                }
              )
            </div>
          </div>
        | Brewery => <Brewery />
        | AboutUs => <AboutUs />
        | Contact => <Contact />
        }
      )
    </div>;
  },
};