let component = ReasonReact.statelessComponent("BeerPointRow");

let make = (~numberOfPoints, ~title, _children) => {
    ...component,
    render: _self =>
        <div className="div-table-row">
            <span className="div-table-col div-fixed-width-col">
                <h4 className="beerPoints">
                (ReasonReact.stringToElement(title))
                </h4>
            </span>
            (
            ReasonReact.arrayToElement(
                BeerPoints.maximumNumberOfPoints
                |> Array.map((i: int) =>
                    <BeerPoints
                        key=(string_of_int(i))
                        points=i
                        numberOfPoints=numberOfPoints
                    />
                    ),
            )
            )
        </div>
};