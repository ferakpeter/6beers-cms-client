let component = ReasonReact.statelessComponent("Selection");

let beerElements = (beers: list(Beer.beer)) =>
  beers
  |> List.map((beer: Beer.beer) =>
       <div key=beer.code>
         <h3> (ReasonReact.stringToElement(beer.name)) </h3>
         <Image className="center" src=beer.bottle.thumbnail />
         <Ratings className="center" ratings=beer.ratings />
       </div>
     )
  |> Array.of_list;

let make = (~beers, ~onClicked, _children) => {
  ...component,
  render: _self =>
    <div className="section" id="selection">
      <div className="container">
        <div className="row">
          <div className="col-md-12">
            <div
              style=(ReactDOMRe.Style.make(~width="90%", ~margin="auto", ()))>
              <Slider slidesToShow=3 dots=false autoplaySpeed=2000>
                (ReasonReact.arrayToElement(beerElements(beers)))
              </Slider>
            </div>
          </div>
        </div>
      </div>
    </div>,
};