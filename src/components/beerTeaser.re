let component = ReasonReact.statelessComponent("BeerTeaser");

let beerElements = (beers: list(Beer.beer)) =>
  beers
  |> List.map((b: Beer.beer) =>
       <div
         style=(ReactDOMRe.Style.make(~marginBottom="10px", ())) key=b.code>
         <h3> (ReasonReact.stringToElement(b.name)) </h3>
         <div style=(ReactDOMRe.Style.make(~margin="5px", ()))>
           <img className="image" src=b.bottleImageLink height="350px" />
         </div>
         <div
           className="tile"
           style=(ReactDOMRe.Style.make(~margin="5px", ()))>
           <div>
             <h4 className="beerPoints">
               (ReasonReact.stringToElement("maltiness"))
             </h4>
             (
               ReasonReact.arrayToElement(
                 BeerPoints.maximumNumberOfPoints
                 |> Array.map((i: int) =>
                      <BeerPoints
                        key=(string_of_int(i))
                        points=i
                        numberOfPoints=b.maltinessRating
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
                        numberOfPoints=b.hoppinessRating
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
                        numberOfPoints=b.bitternessRating
                      />
                    ),
               )
             )
           </div>
         </div>
       </div>
     )
  |> Array.of_list;

let make = (~beers, _children) => {
  ...component,
  render: _self =>
    <div>
      <h2 className="center-block">
        (ReasonReact.stringToElement("Beer"))
      </h2>
      <Slider> (ReasonReact.arrayToElement(beerElements(beers))) </Slider>
    </div>,
};
