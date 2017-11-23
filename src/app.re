type actions =
  /* route Actions */
  | Brewery
  | Beer
  | Order
  | Contact
  | All
  /* User actions */
  | AddBeerToShoppingCart string
  /* external API calls */
  | UpdateAvailableBeers (list Beer.beer)
  | UpdateNews (list Teaser.news);

type state = {
  availableBeers: list Beer.beer,
  shoppingCart: list string,
  news: list Teaser.news,
  selectedRoute: actions
};

let namespace = "6beers-client-app";

external unsafeJsonParse : string => 'a = "JSON.parse" [@@bs.val];

let saveLocally (shoppingCart: list string) =>
  switch (Js.Json.stringifyAny shoppingCart) {
  | None => ()
  | Some stringifiedShoppingCart =>
    Dom.Storage.(localStorage |> setItem namespace stringifiedShoppingCart)
  };

let addBeerToShoppingCart beerCode _event => AddBeerToShoppingCart beerCode;

let component = ReasonReact.reducerComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {
    let shoppingCartBeerCodes =
      switch Dom.Storage.(localStorage |> getItem namespace) {
      | None => []
      | Some shoppingCart => unsafeJsonParse shoppingCart
      };
    {availableBeers: [], shoppingCart: shoppingCartBeerCodes, news: [], selectedRoute: All}
  },
  reducer: fun action state =>
    switch action {
    /* router actions */
    | All => ReasonReact.Update {...state, selectedRoute: All}
    | Brewery => ReasonReact.Update {...state, selectedRoute: Brewery}
    | Beer => ReasonReact.Update {...state, selectedRoute: Beer}
    | Order => ReasonReact.Update {...state, selectedRoute: Order}
    | Contact => ReasonReact.Update {...state, selectedRoute: Contact}
    /* User Actions */
    | AddBeerToShoppingCart beer =>
      let shoppingCart = List.append state.shoppingCart [beer];
      Js.log shoppingCart;
      ReasonReact.UpdateWithSideEffects
        {...state, shoppingCart} (fun _self => saveLocally shoppingCart)
    /* Api actions */
    | UpdateAvailableBeers beers => ReasonReact.Update {...state, availableBeers: beers}
    | UpdateNews news => ReasonReact.Update {...state, news}
    },
  didMount: fun {reduce} => {
    let callReducer (items: Api.apiItems) => {
      reduce (fun _ => UpdateAvailableBeers items.beers) ();
      reduce (fun _ => UpdateNews items.news) ()
    };
    Js.Promise.(
      Bs_fetch.fetch (Cms.absolutePath "index.php/api.html?modul=NewsList&limit=1000") |>
      then_ Bs_fetch.Response.json |>
      then_ (
        fun result => Api.parseConfig result |> Api.mapJsonValuesToState |> callReducer |> resolve
      ) |> ignore
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
    ReasonReact.NoUpdate
  },
  render: fun {state, reduce} => {
    let beers =
      List.map
        (
          fun (b: Beer.beer) =>
            <Beer beer=b key=b.code onOrdered=(reduce (addBeerToShoppingCart b.code)) />
        )
        state.availableBeers;
    <div className="App">
      <Header />
      (
        switch state.selectedRoute {
        | All =>
          <div>
            <div style=(ReactDOMRe.Style.make padding::"20px" margin::"auto" width::"90%" ())>
              <Teaser news=state.news />
              <HorizontalSeparator />
              <Brewery />
              <HorizontalSeparator />
              <BeerDescription />
              <h2> (ReasonReact.stringToElement "Available Beer") </h2>
              <h5> (ReasonReact.stringToElement "(hover or tap to order)") </h5>
              (ReasonReact.arrayToElement (Array.of_list beers))
              <HorizontalSeparator />
              <Contact />
            </div>
            <Footer />
          </div>
        | Beer => <BeerDescription />
        | Brewery => <Brewery />
        | Order => <div> (ReasonReact.arrayToElement (Array.of_list beers)) </div>
        | Contact => <Contact />
        /* Do nothing for non route actions */
        | UpdateAvailableBeers _
        | UpdateNews _
        | AddBeerToShoppingCart _ => ReasonReact.nullElement
        }
      )
    </div>
  }
};
