let url = "https://polar-brook-99163.herokuapp.com/api/contact/";

[@bs.val] external btoa : string => string = "btoa";

type contactRequest = {
  email: string,
  name: string,
  text: string,
};

let createContactRequest = (email, name, text) => {
  let payload = Js.Dict.empty();
  Js.Dict.set(
    payload,
    "subject",
    Js.Json.string("Contact request from " ++ name),
  );
  Js.Dict.set(payload, "html", Js.Json.string(text));
  Js.Dict.set(payload, "to", Js.Json.string(email));
  let credentials = "Basic " ++ btoa("api:key");
  Js.Json.stringify(Js.Json.object_(payload));
};