type ratings =
  | Maltiness(string, int)
  | Hoppiness(string, int)
  | Bitterness(string, int);

let component = ReasonReact.statelessComponent("Ratings");

let ratingsPoints = [|1, 2, 3, 4, 5|];

let beerPoint = (points, numberOfPoints, title, onClick) =>
  <span key=(title ++ string_of_int(points)) className="div-table-col">
    <img
      className=(
        points <= numberOfPoints ?
          "beerPoints" : "beerPoints_notGiven beerPoints"
      )
      src="assets/img/6beers_point.png"
      alt=""
      width="20"
      height="20"
      onClick
    />
  </span>;

let ratingsRow = (title, rating, onClick) =>
  <div
    key=title
    style=(ReactDOMRe.Style.make(~padding="2px", ()))
    className="div-table-row">
    <span className="div-table-col div-fixed-width-col" onClick>
      <h4 className="beerPoints"> (ReasonReact.stringToElement(title)) </h4>
    </span>
    (
      ReasonReact.arrayToElement(
        ratingsPoints
        |> Array.map((i: int) => beerPoint(i, rating, title, onClick)),
      )
    )
  </div>;

let make = (~ratings, ~onClick, ~className: option(string)=?, _children) => {
  ...component,
  render: _self =>
    <div className="center div-table">
      (
        ReasonReact.arrayToElement(
          ratings
          |> Array.map(rating =>
               switch (rating) {
               | Maltiness(title, rating) =>
                 ratingsRow(title, rating, onClick)
               | Hoppiness(title, rating) =>
                 ratingsRow(title, rating, onClick)
               | Bitterness(title, rating) =>
                 ratingsRow(title, rating, onClick)
               }
             ),
        )
      )
    </div>,
};