type beer = {
  id: int,
  code: string,
  name: string,
  description: string,
  detail: string,
  priceSmall: float,
  priceLarge: float,
  quantitySmall: int,
  quantityLarge: int,
  bottleImageLink: string,
  glassImageLink: string,
  labelImageLink: string
};

external order: string => unit = "order" [@@bs.val];

let clicked = fun code _event => { Js.log "clicked"; order code; };

let component = ReasonReact.statelessComponent "Beer";

let make ::beer _children => {
  ...component,
  render: fun _self =>
  <div className="container">
    <div className="row">
        <ReactFlipCard>
          <div>
            <h3 className="tile-title"> (ReasonReact.stringToElement beer.name) </h3>
            <br />
            <img className="image" src=beer.bottleImageLink height="350px" />
            <div> <br /> </div>
            <div dangerouslySetInnerHTML={"__html": beer.description} />
            /* <button onClick=clicked className="btn btn-success btn-large btn-block"> (ReasonReact.stringToElement "Order") </button> */
          </div>
          <div>
            <h3 className="tile-title"> (ReasonReact.stringToElement beer.name) </h3>
            <br />
            <img className="img-responsive center-block" src=beer.labelImageLink />
            <br />
            <div dangerouslySetInnerHTML={"__html": beer.detail} />
            <button onClick=(clicked beer.code) className="btn btn-success btn-large btn-block"> (ReasonReact.stringToElement "Order") </button>
          <br />
          </div>
        </ReactFlipCard>
    </div>
  </div>
};
