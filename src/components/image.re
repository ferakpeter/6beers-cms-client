/* [@bs.module] external style : Js.t({..}) = "./image.module.scss"; */
type image =
  | Thumbnail(option(string), option(int))
  | Fullsize(option(string), option(int));

let component = ReasonReact.statelessComponent("Image");

let make = (~src, ~className: option(string)=?, ~onClick, _children) => {
  ...component,
  render: _self =>
    switch (src) {
    | Thumbnail(Some(imageSource), Some(height)) =>
      <img
        className=(
          switch (className) {
          | Some(className) => className
          | None => ""
          }
        )
        src=imageSource
        height=(string_of_int(height) ++ "px")
        onClick
      />
    | Thumbnail(Some(imageSource), None) =>
      <img
        className=(
          switch (className) {
          | Some(className) => className
          | None => ""
          }
        )
        src=imageSource
        height="150px"
        onClick
      />
    | Fullsize(Some(imageSource), Some(height)) =>
      <img
        className=(
          switch (className) {
          | Some(className) => className
          | None => ""
          }
        )
        src=imageSource
        height=(string_of_int(height) ++ "px")
        onClick
      />
    | Fullsize(Some(imageSource), None) =>
      <img
        className=(
          switch (className) {
          | Some(className) => className
          | None => ""
          }
        )
        src=imageSource
        height="500px"
        onClick
      />
    | _ => <img src="assets/img/fallback.jpg" height="350px" />
    },
};