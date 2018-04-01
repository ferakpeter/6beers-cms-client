let component = ReasonReact.statelessComponent("HorizontalSeparator");

let make = (~height, ~inverseColors, _children) => {
  ...component,
  render: _self =>
    <img
        className="img-responsive center-block"
        src=(inverseColors ? "assets/img/6beers-inverse.svg" : "assets/img/6beers.svg")
        style=(ReactDOMRe.Style.make(~height=height, ()))
    />,
};
