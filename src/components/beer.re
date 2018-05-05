type graphic = {
  thumbnail: Image.image,
  fullsize: Image.image,
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
    switch (beer) {
    | Preview(beer) =>
      <div style=(ReactDOMRe.Style.make(~padding="5px", ())) key=beer.code>
        <h3 style=(ReactDOMRe.Style.make(~marginBottom="5px", ()))>
          (ReasonReact.stringToElement(beer.name))
        </h3>
        <Image src=beer.bottle.thumbnail className="center margin-bottom" />
        <Ratings ratings=beer.ratings />
      </div>
    | Detail(beer) =>
      <div className="container">
        <div className="row">
          <div className="tile col-md-12">
            <h1 className="tile-title">
              (ReasonReact.stringToElement(beer.name))
            </h1>
            <h5 className="tile-title">
              (ReasonReact.stringToElement(beer.sort))
            </h5>
            <br />
            <Image src=beer.bottle.fullsize className="center" />
            <br />
            <div dangerouslySetInnerHTML={"__html": beer.description} />
            <div dangerouslySetInnerHTML={"__html": beer.detail} />
            <button
              onClick=(clicked(beer.name))
              className="btn btn-success btn-large btn-block">
              (ReasonReact.stringToElement("Order"))
            </button>
          </div>
        </div>
      </div>
    },
};