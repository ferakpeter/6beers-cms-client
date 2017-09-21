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

/* let click _event _self => Js.log "clicked!"; */

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

    let callReducer (items:Api.apiItems) => {
        reduce (fun _ => SetAvailableBeers items.beers) ();
        reduce (fun _ => SetNews items.news) (); };

    Js.Promise.(
      Bs_fetch.fetch (Cms.absolutePath "index.php/api.html?modul=NewsList&limit=1000")
        |> then_ Bs_fetch.Response.json
        |> then_ (fun result => { Api.parseConfig result
        |> Api.mapJsonValuesToState
        |> callReducer
        |> resolve }) |> ignore
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
  render: fun {state} => {
    let beers = List.map (fun (b:Beer.beer) => <Beer beer=b key=b.code /> ) state.availableBeers;

    <div className="App">

      <Header />

      <div>

      (switch (state.selectedRoute)
          {
            | All => <div>
                <div style=(ReactDOMRe.Style.make padding::"20px" margin::"auto" width::"90%" ())>

                  <Teaser news=state.news />
                  <br />

                  <HorizontalSeparator />

                  <Brewery />

                  <HorizontalSeparator />

                  <BeerDescription />

                  <h2> (ReasonReact.stringToElement "Available Beer") </h2>
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
            | SetAvailableBeers _ | SetNews _ => ReasonReact.nullElement
          })
      </div>

    </div>
  }
};
