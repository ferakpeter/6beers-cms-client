type routes =
  | Loading
  | Brewery
  | Beer
  | Order
  | Contact
  | All;

type actions =
  /* route Actions */
  | Navigate(routes)
  /* User actions */
  | AddBeerToShoppingCart(string)
  /* external API calls */
  | Load
  | ApiCallFailed
  | UpdateAvailableBeers(list(Beer.beer))
  | UpdateNews(list(Teaser.news));

type state = {
  availableBeers: list(Beer.beer),
  shoppingCart: list(string),
  news: list(Teaser.news),
  selectedRoute: routes
};

let namespace = "6beers-client-app";

[@bs.val] external unsafeJsonParse : string => 'a = "JSON.parse";

let saveLocally = (shoppingCart: list(string)) =>
  switch (Js.Json.stringifyAny(shoppingCart)) {
  | None => ()
  | Some(stringifiedShoppingCart) =>
    Dom.Storage.(localStorage |> setItem(namespace, stringifiedShoppingCart))
  };

let urlToSelectedRoute = hash =>
  switch(hash) {
    | "beer"  => Beer
    | "brewery" => Brewery
    |"contact" => Contact
    | "order" => Order
    | _ => All
  };

let addBeerToShoppingCart = (beerCode, _event) => AddBeerToShoppingCart(beerCode);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    let shoppingCartBeerCodes =
      switch Dom.Storage.(localStorage |> getItem(namespace)) {
      | None => []
      | Some(shoppingCart) => unsafeJsonParse(shoppingCart)
      };
    {availableBeers: [], shoppingCart: shoppingCartBeerCodes, news: [], selectedRoute: urlToSelectedRoute(ReasonReact.Router.dangerouslyGetInitialUrl().hash)}
  },
  reducer: (action, state) =>
    switch (action) {
    /* router actions */
    | Navigate(page) => ReasonReact.Update({...state, selectedRoute: page })
    /* User Actions */
    | AddBeerToShoppingCart(beer) =>
      let shoppingCart = List.append(state.shoppingCart, [beer]);
      Js.log(shoppingCart);
      ReasonReact.UpdateWithSideEffects({...state, shoppingCart}, (_self => saveLocally(shoppingCart)))
    /* Api actions */
    | Load =>
    ReasonReact.UpdateWithSideEffects(
        {...state, selectedRoute: Loading},
        (
          self =>
            Js.Promise.(
              Fetch.fetch(Cms.absolutePath("index.php/api.html?modul=NewsList&limit=1000"))
              |> then_(Fetch.Response.json)
              |> then_(json =>
                  json
                  |> Api.parseConfig
                  |> Api.mapJsonValuesToState
                  |> (items => { self.send(UpdateAvailableBeers(items.beers));
                                 self.send(UpdateNews(items.news)); })
                  |> resolve
                )
              |> catch(_err =>
                  Js.Promise.resolve(self.send(ApiCallFailed))
                )
              |> ignore
            )
        ),
      )
    | UpdateAvailableBeers(beers) => ReasonReact.Update({...state, availableBeers: beers})
    | UpdateNews(news) => ReasonReact.Update({...state, news})
    },
  didMount: self => {
    self.send(Load);
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
      List.map
        (
          (b: Beer.beer) =>
            <Beer beer=b key=b.code onOrdered=(_event => send(AddBeerToShoppingCart(b.code))) />
        , state.availableBeers)
        ;
    <div className="App">
      <Header />
      (
        switch state.selectedRoute {
        | All =>
          <div>
            <div style=(ReactDOMRe.Style.make(~padding="20px", ~margin="auto", ~width="90%", ()))>
              <Teaser news=state.news />
              <BeerTeaser beers=state.availableBeers />
              <HorizontalSeparator />
              <Brewery />
              <HorizontalSeparator />
              <BeerDescription />
              <h2> (ReasonReact.stringToElement("Available Beer")) </h2>
              (ReasonReact.arrayToElement(Array.of_list(beers)))
              <HorizontalSeparator />
              <Contact />
            </div>
            <Footer />
          </div>
        | Beer => <BeerDescription />
        | Brewery => <Brewery />
        | Order => <div>
            <h2> (ReasonReact.stringToElement("Available Beer")) </h2>
            (ReasonReact.arrayToElement(Array.of_list(beers)))
          </div>
        | Contact => <Contact />
        | Loading =>
          <div>
            <div style=(ReactDOMRe.Style.make(~padding="20px", ~margin="auto", ~width="90%", ()))>
              <HorizontalSeparator />
              <Brewery />
              <HorizontalSeparator />
              <BeerDescription />
              <h2> (ReasonReact.stringToElement("Available Beer")) </h2>
              (ReasonReact.arrayToElement(Array.of_list(beers)))
              <HorizontalSeparator />
              <Contact />
            </div>
            <Footer />
          </div>
        }
      )
    </div>
  }
};
