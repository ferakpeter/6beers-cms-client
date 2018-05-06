/*import { Facebook } from 'react-content-loader'*/
let component = ReasonReact.statelessComponent("ContentLoader");

[@bs.module "react-content-loader"]
external reactContentLoader : ReasonReact.reactClass = "Facebook";

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=reactContentLoader,
    ~props={"test": "test"},
    children,
  );