type news = {
  id: string,
  title: string,
  imageLink: string,
  link: option string,
  content: string
};

module Slider = {
  external reactSlick : ReasonReact.reactClass = "default" [@@bs.module "react-slick"];

  let make children =>
    ReasonReact.wrapJsForReason
      reactClass::reactSlick
      props::{
        "dots": Js.Boolean.to_js_boolean true,
        "infinite": Js.Boolean.to_js_boolean true,
        "slidesToShow": 3,
        "slidesToScroll": 1,
        "lazyLoad": Js.Boolean.to_js_boolean true,
        "autoplay": Js.Boolean.to_js_boolean true,
        "autoplaySpeed": 5000,
        "responsive":  [|
          {
            "breakpoint": 1024,
            "settings": {
              "slidesToShow": 2
            }
          },
          {
            "breakpoint": 750,
            "settings": {
              "slidesToShow": 1
            }
          }, |]
      }
      children;
};

let component = ReasonReact.statelessComponent "Teaser";

let newsElements (news:list news) => news |> List.map (fun (n:news) => {
  <div style=(ReactDOMRe.Style.make marginBottom::"10px" ()) key=n.id>
    <h3> (ReasonReact.stringToElement n.title) </h3>
    <div style=(ReactDOMRe.Style.make margin::"5px" ())>
    (switch (n.link) {
      | None => <img className="img-responsive img-rounded" src=n.imageLink />;
      | Some link => link == "" ?
        <img className="img-responsive img-rounded" src=n.imageLink /> :
        <a href=link target="_blank"> <img className="img-responsive img-rounded" src=n.imageLink /> </a>;
    })
    </div>
    <div className="tile" style=(ReactDOMRe.Style.make margin::"5px" ()) dangerouslySetInnerHTML={"__html": n.content} />
  </div>
}) |> Array.of_list;

let make ::news _children => {
    ...component,
    render: fun _self =>
      <div>
        <h2 className="center-block"> (ReasonReact.stringToElement "News") </h2>
        <Slider>
          (ReasonReact.arrayToElement (newsElements news))
        </Slider>
        <br />
      </div>
};
