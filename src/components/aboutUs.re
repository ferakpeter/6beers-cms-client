let component = ReasonReact.statelessComponent("BeerDescription");

let make = _children => {
  ...component,
  render: _self =>
    <div className="section" id="beer">
      <div className="row">
        <h2> (ReasonReact.stringToElement("About Us")) </h2>
        <img
          className="img-rounded img-responsive"
          src="assets/img/brewery.jpg"
        />
      </div>
      <div className="row margin-top-l" />
      <div className="row">
        <div className="col-md-12">
          <div className="card">
            <h3>
              (
                ReasonReact.stringToElement(
                  "Award Winning Craft Beer from Wienerwald",
                )
              )
            </h3>
            <p>
              (
                ReasonReact.stringToElement(
                  "6 beers is a small private brewery from the Wienerwald region south of Vienna. We aim to create a unique drinking experience with outstanding Craftbeer that enriches every meal. To get a feeling of what our beers offer browse through our selection and get more information in the details for each beer type.",
                )
              )
            </p>
          </div>
        </div>
      </div>
    </div>,
};