let component = ReasonReact.statelessComponent("BeerTeaser");

let fallbackDefaultImageHeight = (height) =>
  switch height {
  | Some(height) => height
  | None => 200
  };

let beerElements = (beers: list(Beer.beer), onMouseOver, onMouseOut) =>
  beers
  |> List.map((b: Beer.beer) =>
       <div key=b.code>
         <h3> (ReasonReact.stringToElement(b.name)) </h3>
         <div>
           <img className="image center" src=b.bottleImageLink height=(string_of_int(fallbackDefaultImageHeight(b.bottleImageHeightSmall)) ++ "px")
           onMouseOver=(onMouseOver(b.id))
           onMouseOut=(onMouseOut(b.id))
           />
         </div>
         <div className="tile div-table center">
           <BeerPointRow numberOfPoints=b.maltinessRating title="maltiness" />
           <BeerPointRow numberOfPoints=b.hoppinessRating title="hoppiness" />
           <BeerPointRow numberOfPoints=b.bitternessRating title="bitterness" />
         </div>
       </div>
     )
  |> Array.of_list;

let make = (~beers, ~onMouseOver, ~onMouseOut, _children) => {
  ...component,
  render: _self =>
    <div>
      <Slider slidesToShow=4 dots=false autoplaySpeed=2000> (ReasonReact.arrayToElement(beerElements(beers, onMouseOver, onMouseOut))) </Slider>
    </div>,
};
