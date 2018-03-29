let component = ReasonReact.statelessComponent("HorizontalSeparator");

let make = (~height, _children) => {
  ...component,
  render: _self =>
    <img
        className="img-responsive center-block"
        src="assets/img/logo.png"
        style=(ReactDOMRe.Style.make(~height=height, ()))
    />,
};
