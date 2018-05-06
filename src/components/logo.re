let component = ReasonReact.statelessComponent("HorizontalSeparator");

let make = (~height, ~inverseColors, ~className, _children) => {
  ...component,
  render: _self =>
    <img
      className
      src=(
        inverseColors ?
          "assets/img/6beers-inverse.svg" : "assets/img/6beers.svg"
      )
      style=(ReactDOMRe.Style.make(~height, ()))
    />,
};