type beer = {
  id: int,
  code: string,
  name: string,
  description: string,
  priceSmall: float,
  priceLarge: float,
  quantitySmall: int,
  quantityLarge: int,
  bottleImageLink: string,
  glassImageLink: string,
  labelImageLink: string
};

let clicked = fun _event => { Js.log "clicked"; };

let component = ReasonReact.statelessComponent "Beer";

let make ::beer _children => {
  ...component,
  render: fun _self =>
  <div className="container">
    <div className="row">
      <div className="col-md-10">
        <div className="tile">
          <h3 className="tile-title"> (ReasonReact.stringToElement beer.name) </h3>
          <a href="" onClick=(clicked) >
            <img className="image" src=beer.bottleImageLink height="300px" />
          </a>
          <div> <br /> </div>
          <div dangerouslySetInnerHTML={"__html": beer.description} />
          <button className="btn btn-secondary btn-large btn-block"  onClick=clicked> (ReasonReact.stringToElement  "Detail") </button>
          <button onClick=clicked className="btn btn-success btn-large btn-block"> (ReasonReact.stringToElement "Order") </button>
        </div>
      </div>
    </div>
  </div>
};