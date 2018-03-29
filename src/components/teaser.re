type news = {
  id: string,
  title: string,
  imageLink: string,
  link: option(string),
  content: string,
};

let component = ReasonReact.statelessComponent("Teaser");

let newsElements = (news: list(news)) =>
  news
  |> List.map((n: news) =>
       <div style=(ReactDOMRe.Style.make(~marginBottom="10px", ())) key=n.id>
         <h3> (ReasonReact.stringToElement(n.title)) </h3>
         <div style=(ReactDOMRe.Style.make(~margin="5px", ()))>
           (
             switch (n.link) {
             | None =>
               <img className="img-responsive img-rounded" src=n.imageLink />
             | Some(link) =>
               link == "" ?
                 <img
                   className="img-responsive img-rounded"
                   src=n.imageLink
                 /> :
                 <a href=link target="_blank">
                   <img
                     className="img-responsive img-rounded"
                     src=n.imageLink
                   />
                 </a>
             }
           )
         </div>
         <div
           className="tile"
           style=(ReactDOMRe.Style.make(~margin="5px", ()))
           dangerouslySetInnerHTML={"__html": n.content}
         />
       </div>
     )
  |> Array.of_list;

let make = (~news, _children) => {
  ...component,
  render: _self =>
    <div>
      <h2 className="center-block">
        (ReasonReact.stringToElement("News"))
      </h2>
      <Slider slidesToShow=3 dots=true> (ReasonReact.arrayToElement(newsElements(news))) </Slider>
      <br />
    </div>,
};
