let click _event _self => Js.log "clicked!";

let component = ReasonReact.statelessComponent "App";

let make ::title _children => {
  ...component,
  render: fun self =>
    <div className="App">
      <Header />

      

      <div className="footer">

      </div>
    </div>
};
