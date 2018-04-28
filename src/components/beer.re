type graphic = {
  thumbnail: Image.image,
  fullsize: Image.image
};

type beer = { 
  id: int,
  code: string,
  name: string,
  sort: string,
  description: string,
  detail: string,
  priceSmall: float,
  priceLarge: float,
  quantitySmall: int,
  quantityLarge: int,
  bottle: graphic,
  glass: graphic,
  label: graphic,
  ratings: array(Ratings.ratings),
};

type displaySizes =
  | Preview(beer)
  | Detail(beer);

[@bs.val] external order : string => unit = "order";

let clicked = (name, _event) => order(name);

let component = ReasonReact.statelessComponent("Beer");

let make = (~beer, ~onOrdered, _children) => {
  ...component,
  render: _self =>
    switch(beer) {
    | Preview(beer) =>
    <div key=beer.code>
      <h3> (ReasonReact.stringToElement(beer.name)) </h3>
      <Image src=beer.bottle.thumbnail />
      <Ratings ratings=beer.ratings />
    </div>
    | Detail(beer) =>
    <div className="container">
      <div className="row">
        <div className="tile col-md-4">
          <h2 className="tile-title">
            (ReasonReact.stringToElement(beer.name))
          </h2>
          <br />
          <Image src=beer.bottle.fullsize />
          <br />
          <br />
          <div dangerouslySetInnerHTML={"__html": beer.description} />
          <Ratings ratings=beer.ratings />
        </div>
        <div className="tile col-md-4">
          <h2 className="tile-title">
            (ReasonReact.stringToElement(beer.sort))
          </h2>
          <br />
          <Image src=beer.label.thumbnail />
          <br />
          <div dangerouslySetInnerHTML={"__html": beer.detail} />
          <button
            onClick=(clicked(beer.name))
            className="btn btn-success btn-large btn-block">
            (ReasonReact.stringToElement("Order"))
          </button>
          <br />
        </div>
      </div>
    </div>
    }
};
