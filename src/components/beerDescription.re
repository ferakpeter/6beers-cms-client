let component = ReasonReact.statelessComponent "BeerDescription";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="section section-we-do-2" id="beer">
          <div className="container">
              <div className="row">
                <h2> (ReasonReact.stringToElement "Our Beer") </h2>
                  <img className="img-rounded img-responsive" src="assets/img/brewery.jpg" />
              </div>
              <div className="row">
                <br />
              </div>
              <div className="row">
                  <div className="col-md-8">
                      <div className="card">
                          /* <div className="icon">
                            <img className="img-responsive center-block" src="assets/img/icons/png/tap.png" />
                          </div> */
                          <h3> (ReasonReact.stringToElement "Award Winning Craft Beer from Wienerwald") </h3>
                          <p> (ReasonReact.stringToElement "6 beers is a small private brewery from the Wienerwald region south of Vienna. We aim to create a unique drinking experience with outstanding Craftbeer that enriches every meal. To get a feeling of what our beers offer browse through our selection and get more information in the details for each beer type.") </p>
                      </div>
                  </div>
                  <div className="col-md-4">
                      <div className="card">
                          /* <div className="icon">
                            <img className="img-responsive center-block" src="assets/img/icons/png/bottle.png" />
                          </div> */
                          <h3> (ReasonReact.stringToElement "Selection") </h3>
                          <p>
                            (ReasonReact.stringToElement "Bohemian (Lager)") <br />
                            (ReasonReact.stringToElement "Gold Rush (California Common)") <br />
                            (ReasonReact.stringToElement "TropicAle (American Pale Ale)") <br />
                            (ReasonReact.stringToElement "Moonlight (Vermont Imperial IPA)") <br />
                            (ReasonReact.stringToElement "Ryebow (Pale Ale)") <br />
                            (ReasonReact.stringToElement "Houses of the Hops (India Pale Ale)") <br />
                            (ReasonReact.stringToElement "Hey Oh (Coffee Stout)") <br />
                            (ReasonReact.stringToElement "Black Dog (Black IPA)") <br />
                            (ReasonReact.stringToElement "Dark Face (Porter)") <br />
                          </p>
                      </div>
                  </div>
              </div>
          </div>
          /* <div className="row">
              <img className="img-responsive center-block" src="assets/img/logo.png" style=(ReactDOMRe.Style.make height::"100px" ()) />
            </div> */
      </div>
};
