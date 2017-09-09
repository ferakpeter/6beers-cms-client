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
        "dots": true,
        "infinite": true,
        "slidesToShow": 1,
        "slidesToScroll": 1,
        "useCSS": true
      }
      children;
};

let component = ReasonReact.statelessComponent "Teaser";

let newsElements (news:list news) => news |> List.map (fun (n:news) => {
  /* Js.log n; */
  <div key=n.id>
    <h3> (ReasonReact.stringToElement n.title) </h3>
    (switch (n.link) {
      | None => <img className="img-responsive img-rounded center-block" src=n.imageLink />;
      | Some link => link == "" ?
        <img className="img-responsive img-rounded center-block" src=n.imageLink /> :
        <a href=link target="_blank"> <img className="img-responsive img-rounded center-block" src=n.imageLink /> </a>;
    })
    <div dangerouslySetInnerHTML={"__html": n.content} />
  </div>
}) |> Array.of_list;

let make ::news _children => {
    ...component,
    render: fun _self =>
      <div>
        <h2 className="center-block"> (ReasonReact.stringToElement "News") </h2>
        /* <Slider> */
          (ReasonReact.arrayToElement (newsElements news))
        /* </Slider> */
      </div>
};
