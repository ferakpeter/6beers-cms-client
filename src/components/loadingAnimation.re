let component = ReasonReact.statelessComponent("ContentLoader");

type loader =
  | Facebook
  | Instagram
  | Code
  | List
  | BulletPoints;

[@bs.module "react-content-loader"]
external facebookAnimation : ReasonReact.reactClass = "Facebook";

[@bs.module "react-content-loader"]
external instagramAnimation : ReasonReact.reactClass = "Instagram";

[@bs.module "react-content-loader"]
external listAnimation : ReasonReact.reactClass = "List";

[@bs.module "react-content-loader"]
external codeAnimation : ReasonReact.reactClass = "Code";

[@bs.module "react-content-loader"]
external bulletpointsAnimation : ReasonReact.reactClass = "BulletPoints";

let make = (~loader: loader, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=
      switch (loader) {
      | Facebook => facebookAnimation
      | Instagram => instagramAnimation
      | List => listAnimation
      | Code => codeAnimation
      | BulletPoints => bulletpointsAnimation
      },
    ~props={"empty": "value"},
    children,
  );