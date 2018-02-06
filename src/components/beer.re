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
  glassImageLink: string,
  labelImageLink: string,
  maltinessRating: int,
  hoppinessRating: int,
  bitternessRating: int,
  inShoppingCart: bool
};

external order: string => unit = "order" [@@bs.val];

let clicked = fun name _event => { order name; };

module BeerPoints = {
  let component = ReasonReact.statelessComponent "BeerPoints";

  let make ::points ::numberOfPoints _children => {
    ...component,
    render: fun _self =>
        <span className="beerPoints">
          <img className=(points <= numberOfPoints ? "beerPoints-img" : "beerPoints_notGiven beerPoints-img") src="assets/img/6beers_point.png" alt="" width="30" height="30" />
        </span>
  }
};

let component = ReasonReact.statelessComponent "Beer";
let maximumNumberOfPoints = [| 1, 2, 3, 4, 5 |];

let make ::beer ::onOrdered _children => {
  ...component,
  render: fun _self =>
  <div className="container">
    <div className="row">
        <ReactFlipCard>
          <div>
            <h2 className="tile-title"> (ReasonReact.stringToElement beer.name) </h2>
            <br />
            <img className="image" src=beer.bottleImageLink height="350px" />
            <br /> <br />
            <div dangerouslySetInnerHTML={"__html": beer.description} />

            <div>
              <h4> (ReasonReact.stringToElement "maltiness") </h4>
              (ReasonReact.arrayToElement (maximumNumberOfPoints |> Array.map (fun (i:int) => <BeerPoints key=(string_of_int i) points=i numberOfPoints=beer.maltinessRating />)))
            </div>

            <div>
              <h4> (ReasonReact.stringToElement "hoppiness") </h4>
              (ReasonReact.arrayToElement (maximumNumberOfPoints |> Array.map (fun (i:int) => <BeerPoints key=(string_of_int i) points=i numberOfPoints=beer.hoppinessRating />)))
            </div>

            <div>
              <span style=(ReactDOMRe.Style.make ())> <h4> (ReasonReact.stringToElement "bitterness") </h4> </span>
              (ReasonReact.arrayToElement (maximumNumberOfPoints |> Array.map (fun (i:int) => <BeerPoints key=(string_of_int i) points=i numberOfPoints=beer.bitternessRating />)))
            </div>

          </div>
          <div>
            <h2 className="tile-title"> (ReasonReact.stringToElement beer.sort) </h2>
            <br />
            <img className="img-responsive center-block" src=beer.labelImageLink />
            <br />
            <div dangerouslySetInnerHTML={"__html": beer.detail} />
            <button onClick=(clicked beer.name) className="btn btn-success btn-large btn-block"> (ReasonReact.stringToElement "Order") </button>
          <br />
          </div>
        </ReactFlipCard>
    </div>
  </div>
};
