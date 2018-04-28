[@bs.module]
external reactFlipCard : ReasonReact.reactClass = "react-flipcard";

let make = (~className: option(string)=?, ~kind: option(string)=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=reactFlipCard,
    ~props={
      "class": Js.Null_undefined.from_opt(className),
      "type": Js.Null_undefined.from_opt(kind),
      "width": "500px",
      "height": "300px",
    },
    children,
  );
