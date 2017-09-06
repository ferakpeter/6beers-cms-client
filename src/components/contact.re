let component = ReasonReact.statelessComponent "Contact";

external contact: unit => unit = "contact" [@@bs.val];

let clicked = fun _event => { contact; };

let make _children => {
  ...component,
  render: fun _self =>
    <div className="section section-contact" id="contact">
        <div className="container">
          <div className="title">
              <h2> (ReasonReact.stringToElement "Contact us") </h2>
              <p> (ReasonReact.stringToElement "6 beers brewering company") </p>
              <p> (ReasonReact.stringToElement "Margaritenweg 23, 2384 Breitenfurt") </p>
              <p> (ReasonReact.stringToElement "Austria") </p>
              <p> (ReasonReact.stringToElement "Tel.: +43 677 624 168 66") </p>
              <button  className="btn btn-success btn-large"> (ReasonReact.stringToElement "Email") </button>
          </div>
          <div className="row">

            <div id="map-container" style=(ReactDOMRe.Style.make filter::"grayscale(100%)" height::"300px" ()) className="col-md-12 center-block" />

              </div>
              /* <br />
              <img className="img-responsive center-block" src="assets/img/beer/logo.png" style=(ReactDOMRe.Style.make height::"100px" ()) /> */
        </div>
      </div>
};
