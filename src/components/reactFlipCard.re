external reactFlipCard : ReasonReact.reactClass = "react-flipcard" [@@bs.module];

let make className::(className:option string)=? kind::(kind:option string)=? children =>
  ReasonReact.wrapJsForReason
  reactClass::reactFlipCard
  props::{
    "class": Js.Null_undefined.from_opt className,
    "type": Js.Null_undefined.from_opt kind,
    "width": "500px",
    "height": "300px"}
  children;
