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
         <h5> (ReasonReact.stringToElement(n.title)) </h5>
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
    <div className="section" id="selection">
      <div className="container">
        <h2 className="center-block">
          (ReasonReact.stringToElement("News"))
        </h2>
        <div>
          <Slider slidesToShow=3 dots=true autoplaySpeed=5000>
            (ReasonReact.arrayToElement(newsElements(news)))
          </Slider>
          <br />
        </div>
      </div>
    </div>,
};