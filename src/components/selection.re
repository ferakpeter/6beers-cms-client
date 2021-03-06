let component = ReasonReact.statelessComponent("Selection");

let beerElements = (beers: list(Beer.beer), onOrdered) =>
  beers
  |> List.map((beer: Beer.beer) =>
       <div
         className="tile-hover" key=beer.code onClick=(onOrdered(beer.code))>
         <h3> (ReasonReact.string(beer.name)) </h3>
         <Image
           className="center bottom-margin"
           src=beer.bottle.thumbnail
           onClick=(onOrdered(beer.code))
         />
         <Ratings
           className="center"
           ratings=beer.ratings
           onClick=(onOrdered(beer.code))
         />
       </div>
     )
  |> Array.of_list;

let make = (~beers, ~onClicked, _children) => {
  ...component,
  render: self =>
    <div className="section" id="selection">
      <div className="container">
        <div className="row">
          <div className="col-md-12">
            <Slider slidesToShow=3 dots=false autoplaySpeed=2000>
              (ReasonReact.array(beerElements(beers, onClicked)))
            </Slider>
          </div>
        </div>
      </div>
    </div>,
};