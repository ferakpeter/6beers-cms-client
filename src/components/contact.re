let component = ReasonReact.statelessComponent("Contact");

[@bs.val] external contact : string => unit = "contact";

[@bs.val]
external copyEmailToClipboard : string => unit = "copyEmailToClipboard";

[@bs.val] external initMap : unit => unit = "init_map";

let copyEmail = _event => copyEmailToClipboard("");

let openEmail = _event => contact("");

let make = _children => {
  ...component,
  didMount: _self => {
    initMap();
    ReasonReact.NoUpdate;
  },
  render: _self =>
    <div className="section" id="contact">
      <div className="container">
        <div className="title">
          <h2> (ReasonReact.stringToElement("Contact us")) </h2>
          <p> (ReasonReact.stringToElement("6 beers brewering company")) </p>
          <p>
            (
              ReasonReact.stringToElement(
                "Margaritenweg 23, 2384 Breitenfurt Austria",
              )
            )
          </p>
          <p> (ReasonReact.stringToElement("Tel.: +43 677 624 168 66")) </p>
          <p>
            <button onClick=copyEmail className="btn btn-large">
              (
                ReasonReact.stringToElement("Copy E-mail address to clipboard")
              )
            </button>
          </p>
          <p>
            <button onClick=openEmail className="btn btn-success btn-large">
              (ReasonReact.stringToElement("Open E-mail"))
            </button>
          </p>
        </div>
        <div className="row">
          <div
            id="map-container"
            style=(
              ReactDOMRe.Style.make(
                ~filter="grayscale(100%)",
                ~height="300px",
                (),
              )
            )
            className="col-md-12 center-block"
          />
        </div>
      </div>
    </div>,
};