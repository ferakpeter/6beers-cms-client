type ratings = 
  | Maltiness(string, int)
  | Hoppiness(string, int)
  | Bitterness(string, int);
let component = ReasonReact.statelessComponent("Ratings");

let ratingsPoints = [|1, 2, 3, 4, 5|];

let beerPoint = (points, numberOfPoints) => 
    <span className="div-table-col">
      <img
        className=(
          points <= numberOfPoints ?
            "beerPoints" : "beerPoints_notGiven beerPoints"
        )
        src="assets/img/6beers_point.png"
        alt=""
        width="20"
        height="20"
      />
    </span>;

let ratingsRow = (title, rating) =>
  <div className="div-table-row">
    <span className="div-table-col div-fixed-width-col">
        <h4 className="beerPoints">
        (ReasonReact.stringToElement(title))
        </h4>
    </span>
    (ReasonReact.arrayToElement(
        ratingsPoints |> Array.map((i: int) => beerPoint(i, rating))))
  </div>;
  

let make = (~ratings, ~className: option(string)=?, _children) => {
  ...component,
  render: _self => 
    <div className="tile div-table">
      (ReasonReact.arrayToElement(ratings |> Array.map(rating =>  
        switch(rating) {
          | Maltiness(title, rating) => ratingsRow(title, rating)
          | Hoppiness(title, rating) => ratingsRow(title, rating)
          | Bitterness(title, rating) => ratingsRow(title, rating)
        }
      )))
    </div>
};