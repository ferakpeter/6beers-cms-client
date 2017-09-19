let component = ReasonReact.statelessComponent "HorizontalSeparator";

let make _children => {
  ...component,
  render: fun _self =>
    <div>
      <hr> </hr>
      <div className="row">
        <img className="img-responsive center-block" src="assets/img/logo.png" style=(ReactDOMRe.Style.make height::"100px" ()) />
      </div>
    </div>
};
