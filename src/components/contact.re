let component = ReasonReact.statelessComponent("Contact");

[@bs.val] external contact : string => unit = "contact";

[@bs.val]
external copyEmailToClipboard : string => unit = "copyEmailToClipboard";

[@bs.val] external btoa : string => string = "btoa";

[@bs.val] external initMap : unit => unit = "init_map";

type t;

type options = {
  apiKey: string,
  domain: string,
};

/*
 postData('http://example.com/answer', {answer: 42})
   .then(data => console.log(data)) // JSON from `response.json()` call
   .catch(error => console.error(error))

 function postData(url, data) {
   // Default options are marked with *
   return fetch(url, {
     body: JSON.stringify(data), // must match 'Content-Type' header
     cache: 'no-cache', // *default, no-cache, reload, force-cache, only-if-cached
     credentials: 'same-origin', // include, same-origin, *omit
     headers: {
       'user-agent': 'Mozilla/4.0 MDN Example',
       'content-type': 'application/json'
     },
     method: 'POST', // *GET, POST, PUT, DELETE, etc.
     mode: 'cors', // no-cors, cors, *same-origin
     redirect: 'follow', // manual, *follow, error
     referrer: 'no-referrer', // *client, no-referrer
   })
   .then(response => response.json()) // parses response to JSON
 }
 */
let submitContactForm = _event => {
  let payload = Js.Dict.empty();
  Js.Dict.set(payload, "subject", Js.Json.string("test"));
  Js.Dict.set(payload, "html", Js.Json.string("test1"));
  let credentials = "Basic " ++ btoa("api:key");
  Js.log(credentials);
  Js.Promise.(
    Fetch.fetchWithInit(
      "https://polar-brook-99163.herokuapp.com/api/submit/"
      ++ "ferak.peter@gmail.com",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
        ~headers=
          Fetch.HeadersInit.makeWithArray([|
            ("Content-Type", "application/x-www-form-urlencoded"),
            (
              "Access-Control-Allow-Methods",
              "GET,PUT,POST,DELETE,PATCH,OPTIONS",
            ),
          |]),
        /* ~credentials=Include, */
        ~mode=NoCORS,
        /* ~referrer="no-referrer",
           ~referrerPolicy=NoReferrer,
           ~cache=NoCache,
           ~redirect=Follow,
           ~integrity="",
           ~keepalive=true, */
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => Js.log(json) |> resolve)
    |> ignore
  );
};

let copyEmail = _event => copyEmailToClipboard("");

let openEmail = _event => contact("");

let make = _children => {
  ...component,
  didMount: _self => {
    initMap();
    ReasonReact.NoUpdate;
  },
  render: _self =>
    <div className="section" id="contact">
      <div> <h2> (ReasonReact.stringToElement("Contact us")) </h2> </div>
      <p> (ReasonReact.stringToElement("6 beers brewering company")) </p>
      <p>
        (
          ReasonReact.stringToElement(
            "Margaritenweg 23, 2384 Breitenfurt Austria",
          )
        )
      </p>
      <p> (ReasonReact.stringToElement("Tel.: +43 677 624 168 66")) </p>
      <p>
        <button onClick=copyEmail className="btn btn-large">
          (ReasonReact.stringToElement("Copy E-mail address to clipboard"))
        </button>
      </p>
      <p>
        <button
          onClick=submitContactForm className="btn btn-success btn-large">
          (ReasonReact.stringToElement("Open E-mail"))
        </button>
      </p>
      <div className="row">
        <div
          id="map-container"
          style=(
            ReactDOMRe.Style.make(
              ~filter="grayscale(100%)",
              ~height="300px",
              (),
            )
          )
          className="col-md-12 center-block"
        />
      </div>
    </div>,
};