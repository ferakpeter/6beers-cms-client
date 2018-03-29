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
  bottleImageLink: string,
  bottleImageHeightSmall: option(int),
  bottleImageHeightLarge: option(int),
  glassImageLink: string,
  glassImageHeightSmall: option(int),
  glassImageHeightLarge: option(int),
  labelImageLink: string,
  labelImageHeightSmall: option(int),
  labelImageHeightLarge: option(int),
  maltinessRating: int,
  hoppinessRating: int,
  bitternessRating: int,
  inShoppingCart: bool,
};

[@bs.val] external order : string => unit = "order";

let clicked = (name, _event) => order(name);

let component = ReasonReact.statelessComponent("Beer");

let make = (~beer, ~onOrdered, _children) => {
  ...component,
  render: _self =>
    <div className="container">
      <div className="row">
        <div className="tile col-md-4">
          <h2 className="tile-title">
            (ReasonReact.stringToElement(beer.name))
          </h2>
          <br />
          <img className="image" src=beer.bottleImageLink height="350px" />
          <br />
          <br />
          <div dangerouslySetInnerHTML={"__html": beer.description} />
          <div>
            <h4> (ReasonReact.stringToElement("maltiness")) </h4>
            (
              ReasonReact.arrayToElement(
                BeerPoints.maximumNumberOfPoints
                |> Array.map((i: int) =>
                     <BeerPoints
                       key=(string_of_int(i))
                       points=i
                       numberOfPoints=beer.maltinessRating
                     />
                   ),
              )
            )
          </div>
          <div>
            <h4> (ReasonReact.stringToElement("hoppiness")) </h4>
            (
              ReasonReact.arrayToElement(
                BeerPoints.maximumNumberOfPoints
                |> Array.map((i: int) =>
                     <BeerPoints
                       key=(string_of_int(i))
                       points=i
                       numberOfPoints=beer.hoppinessRating
                     />
                   ),
              )
            )
          </div>
          <div>
            <span style=(ReactDOMRe.Style.make())>
              <h4> (ReasonReact.stringToElement("bitterness")) </h4>
            </span>
            (
              ReasonReact.arrayToElement(
                BeerPoints.maximumNumberOfPoints
                |> Array.map((i: int) =>
                     <BeerPoints
                       key=(string_of_int(i))
                       points=i
                       numberOfPoints=beer.bitternessRating
                     />
                   ),
              )
            )
          </div>
        </div>
        <div className="tile col-md-4">
          <h2 className="tile-title">
            (ReasonReact.stringToElement(beer.sort))
          </h2>
          <br />
          <img
            className="img-responsive center-block"
            src=beer.labelImageLink
          />
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
    </div>,
};
