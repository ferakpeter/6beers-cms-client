let component = ReasonReact.statelessComponent("BeerPoints");

let maximumNumberOfPoints = [|1, 2, 3, 4, 5|];

let make = (~points, ~numberOfPoints, _children) => {
  ...component,
  render: _self =>
    <span className="beerPoints">
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
    </span>,
};
