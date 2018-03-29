let component = ReasonReact.statelessComponent("Slider");

[@bs.module "react-slick"]
external reactSlick : ReasonReact.reactClass = "default";

let make = (~slidesToShow, ~dots, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=reactSlick,
    ~props={
      "dots": Js.Boolean.to_js_boolean(dots),
      "infinite": Js.Boolean.to_js_boolean(true),
      "slidesToShow": slidesToShow,
      "slidesToScroll": 1,
      "lazyLoad": Js.Boolean.to_js_boolean(true),
      "autoplay": Js.Boolean.to_js_boolean(true),
      "autoplaySpeed": 5000,
      "responsive": [|
        {
          "breakpoint": 1024,
          "settings": {
            "slidesToShow": 2,
          },
        },
        {
          "breakpoint": 750,
          "settings": {
            "slidesToShow": 1,
          },
        },
      |],
    },
    children,
  );
