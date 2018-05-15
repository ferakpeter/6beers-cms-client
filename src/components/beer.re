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
        <img
          src="assets/img/soldout.svg"
          alt="soldout"
          className="tile-hot-ribbon"
        />
        <h3 style=(ReactDOMRe.Style.make(~marginBottom="5px", ()))>
          (ReasonReact.stringToElement(beer.name))
        </h3>
        <Image
          src=beer.bottle.thumbnail
          className="center margin-bottom"
          onClick=onOrdered
        />
        <Ratings ratings=beer.ratings onClick=onOrdered />
      </div>
    | Detail(beer) =>
      <div className="row tile">
        <div className="col-12 margin-xl">
          <h2 className="tile-title margin-m">
            (ReasonReact.stringToElement(beer.name))
          </h2>
          <h3 className="tile-title">
            (ReasonReact.stringToElement(beer.sort))
          </h3>
        </div>
        <div className="col-md-4">
          <Image
            src=beer.bottle.fullsize
            className="center"
            onClick=onOrdered
          />
        </div>
        <div className="col-md-4 padding-l">
          <Ratings ratings=beer.ratings onClick=onOrdered />
        </div>
        <div className="col-md-4">
          <h5> (ReasonReact.stringToElement("Description")) </h5>
          <div dangerouslySetInnerHTML={"__html": beer.description} />
        </div>
        <div className="col-md-8">
          <h5> (ReasonReact.stringToElement("Details")) </h5>
          <div dangerouslySetInnerHTML={"__html": beer.detail} />
        </div>
        <div className="col-md-12 margin-l">
          <button
            onClick=(clicked(beer.name))
            className="btn btn-success btn-large btn-block">
            (ReasonReact.stringToElement("Order"))
          </button>
        </div>
      </div>
    },
};