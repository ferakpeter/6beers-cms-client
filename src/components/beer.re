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

module ReactFlipCard = {
    external reactFlipCard : ReasonReact.reactClass = "react-flipcard" [@@bs.module];
    /* let component = reactFlipCard; */

    let make kind::(kind:option string)=? children =>
      ReasonReact.wrapJsForReason
      reactClass::reactFlipCard
      props::{
        "type": Js.Null_undefined.from_opt kind,
        "width": "500px",
        "height": "300px"}
      children;
};


/* external blockquote : ReactRe.reactClass = "Blockquote" [@@bs.module "rebass"]; */

/*
let reactFlipCard = makeFlipCard "render" [@@bs.send]; */

let clicked = fun _event => { Js.log "clicked"; };

let component = ReasonReact.statelessComponent "Beer";

let make ::beer _children => {
  ...component,
  render: fun _self =>
  <div className="container">
    <div className="row">
      <div className="col-md-12">
        <ReactFlipCard>
          <div className="tile center-block">
            <h3 className="tile-title"> (ReasonReact.stringToElement beer.name) </h3>
            <br />
            <a href="" onClick=(clicked) >
              <img className="image" src=beer.bottleImageLink height="300px" />
            </a>
            <div> <br /> </div>
            <div dangerouslySetInnerHTML={"__html": beer.description} />
            <button onClick=clicked className="btn btn-success btn-large btn-block"> (ReasonReact.stringToElement "Order") </button>
          </div>
          <div>
            <h3 className="tile-title"> (ReasonReact.stringToElement beer.name) </h3>
            <br />
            <img className="img-responsive center-block" src=beer.labelImageLink />
            <br />
            <div dangerouslySetInnerHTML={"__html": beer.detail} />
            <button  className="btn btn-success btn-large btn-block"> (ReasonReact.stringToElement "Order") </button>
          <br />
          </div>
        </ReactFlipCard>
      </div>
    </div>
  </div>
};
