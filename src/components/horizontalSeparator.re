let component = ReasonReact.statelessComponent("HorizontalSeparator");

let make = _children => {
  ...component,
  render: _self =>
    <hr />,
};
