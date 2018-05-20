type routes =
  | Brewery
  | Beer(option(string))
  | AboutUs
  | Contact
  | Terms
  | All;

let urlToSelectedRoute = hash =>
  switch (hash) {
  | "beer" => Beer(None)
  | "brewery" => Brewery
  | "contact" => Contact
  | "aboutus" => AboutUs
  | "termsconditions" => Terms
  | _ =>
    if (hash != "") {
      Beer(Some(hash));
    } else {
      All;
    }
  };

type actions =
  /* route Actions */
  | Navigate(routes)
  /* User actions */
  | AddBeerToShoppingCart(string)
  | SelectBeer(string)
  /* external API calls */
  | LoadApi
  | ApiCallFailed
  | UpdateUi(list(Beer.beer), list(Teaser.news));

type apiStatus =
  | Loading
  | Loaded
  | Failed;

type state = {
  availableBeers: list(Beer.beer),
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
    | exn => Js.log("local storage not available in this browser")
    }
  };

let push = (path, event) => {
  ReactEventRe.Mouse.preventDefault(event);
  ReasonReact.Router.push("#" ++ path);
};

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
    | SelectBeer(beerCode) =>
      ReasonReact.Update({...state, selectedRoute: Beer(Some(beerCode))})
    /* Api actions */
    | LoadApi =>
      ReasonReact.UpdateWithSideEffects(
        {...state, apiStatus: Loading},
        (
          self =>
            Js.Promise.(
              Fetch.fetch(
                CmsApi.absolutePath(
                  "index.php/api.html?modul=NewsList&limit=1000",
                ),
              )
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> CmsApi.parseConfig
                   |> CmsApi.mapJsonValuesToState
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
      <div className="container">
        (
          switch (state.selectedRoute) {
          | All =>
            <div>
              <div>
                <div className="section margin-top-l" id="selection-container">
                  (
                    switch (state.apiStatus) {
                    | Failed
                    | Loading => <LoadingAnimation loader=Facebook />
                    | Loaded =>
                      <Selection
                        beers=(List.map(beer => beer, state.availableBeers))
                        onClicked=push
                      />
                    }
                  )
                </div>
                <HorizontalSeparator />
                <Brewery />
                <HorizontalSeparator />
                <div className="section" id="selection">
                  <h2 className="center-block">
                    (ReasonReact.stringToElement("News"))
                  </h2>
                  <div>
                    (
                      switch (state.apiStatus) {
                      | Failed
                      | Loading => <LoadingAnimation loader=Instagram />
                      | Loaded => <Teaser news=state.news />
                      }
                    )
                  </div>
                </div>
                <HorizontalSeparator />
                <AboutUs />
                <HorizontalSeparator />
                <Contact />
                <Logo
                  className="img-responsive center-block"
                  height="200px"
                  inverseColors=false
                />
              </div>
            </div>
          | Beer(beerCode) =>
            <div className="section">
              (
                switch (beerCode) {
                | None =>
                  <div>
                    <h2> (ReasonReact.stringToElement("Beer")) </h2>
                    (ReasonReact.arrayToElement(Array.of_list(beers)))
                  </div>
                | Some(code) =>
                  switch (
                    List.find(
                      (beer: Beer.beer) => beer.code == code,
                      state.availableBeers,
                    )
                  ) {
                  | beer =>
                    <div className="row margin-top-l">
                      <Beer
                        beer=(Detail(beer))
                        key=beer.code
                        onOrdered=(
                          _event => send(AddBeerToShoppingCart(beer.code))
                        )
                      />
                    </div>
                  | exception Not_found => ReasonReact.nullElement
                  }
                }
              )
            </div>
          | Brewery => <Brewery />
          | AboutUs => <AboutUs />
          | Contact => <Contact />
          | Terms => <div> <Terms /> </div>
          }
        )
      </div>
      <div> <Footer /> </div>
    </div>;
  },
};