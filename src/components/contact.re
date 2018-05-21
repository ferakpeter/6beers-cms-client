[@bs.val] external contact : string => unit = "contact";

[@bs.val]
external copyEmailToClipboard : string => unit = "copyEmailToClipboard";

[@bs.val] external initMap : unit => unit = "init_map";

type t;

type options = {
  apiKey: string,
  domain: string,
};

type action =
  | Submit
  | KeyDown(int)
  | ChangeName(string)
  | ChangeEmail(string)
  | ChangeText(string)
  | Validate
  | ApiCallSucceeded
  | ApiCallFailed
  | Reset;

type emailApiStatus =
  | Idle
  | Loading
  | Success
  | Failed;

type requiredString = {
  isValid: bool,
  value: string,
  validator: Js.Re.t,
};

type state = {
  status: emailApiStatus,
  name: requiredString,
  email: requiredString,
  text: requiredString,
};

let component = ReasonReact.reducerComponent("Contact");

let submitContactForm = state => {
  let req =
    EmailApi.createContactRequest(
      state.name.value,
      state.email.value,
      state.text.value,
    );
  ReasonReact.UpdateWithSideEffects(
    {...state, status: Loading},
    self =>
      Js.Promise.(
        Fetch.fetchWithInit(
          EmailApi.url,
          Fetch.RequestInit.make(
            ~method_=Post,
            ~body=Fetch.BodyInit.make(req),
            ~headers=
              Fetch.HeadersInit.makeWithArray([|
                ("Accept", "application/json"),
                ("Content-Type", "application/json"),
                (
                  "Access-Control-Allow-Methods",
                  "GET,PUT,POST,DELETE,PATCH,OPTIONS",
                ),
              |]),
            /* ~credentials=Include, */
            ~mode=CORS,
            ~referrer="no-referrer",
            ~referrerPolicy=NoReferrer,
            ~cache=NoCache,
            ~redirect=Follow,
            ~integrity="",
            ~keepalive=false,
            (),
          ),
        )
        |> then_(Fetch.Response.json)
        |> then_(json => {
             Js.log(json);
             Js.Promise.resolve(self.send(ApiCallSucceeded));
           })
        |> catch(error => {
             Js.log(error);
             Js.Promise.resolve(self.send(ApiCallFailed));
           })
        |> ignore
      ),
  );
};

let copyEmail = _event => copyEmailToClipboard("");

let openEmail = _event => contact("");

let emptyState = {
  status: Idle,
  name: {
    isValid: false,
    value: "",
    validator: Js.Re.fromString(".+"),
  },
  email: {
    isValid: false,
    value: "",
    validator:
      Js.Re.fromString(
        "^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$",
      ),
  },
  text: {
    isValid: true,
    value: "",
    validator: Js.Re.fromString(".+"),
  },
};

let make = _children => {
  ...component,
  didMount: _self => {
    initMap();
    ReasonReact.NoUpdate;
  },
  initialState: () => emptyState,
  reducer: action =>
    switch (action) {
    | Submit => (state => submitContactForm(state))
    | ChangeName(text) => (
        state => {
          Js.log(Js.Re.test(state.name.value, state.name.validator));
          ReasonReact.Update({
            ...state,
            name: {
              ...state.name,
              value: text,
              isValid: Js.Re.test(state.name.value, state.name.validator),
            },
          });
        }
      )
    | Validate => (
        state =>
          ReasonReact.Update({
            ...state,
            name: {
              ...state.name,
              isValid: Js.Re.test(state.name.value, state.name.validator),
            },
            email: {
              ...state.email,
              isValid: Js.Re.test(state.email.value, state.email.validator),
            },
            text: {
              ...state.text,
              isValid: Js.Re.test(state.text.value, state.text.validator),
            },
          })
      )
    | ChangeEmail(text) => (
        state =>
          ReasonReact.Update({
            ...state,
            email: {
              ...state.email,
              value: text,
              isValid: Js.Re.test(state.email.value, state.email.validator),
            },
          })
      )
    | ChangeText(text) => (
        state =>
          ReasonReact.Update({
            ...state,
            text: {
              ...state.text,
              value: text,
              isValid: Js.Re.test(state.text.value, state.text.validator),
            },
          })
      )
    | KeyDown(13) => (state => submitContactForm(state))
    | KeyDown(_) => (_state => ReasonReact.NoUpdate)
    | ApiCallSucceeded => (
        state => ReasonReact.Update({...state, status: Success})
      )
    | ApiCallFailed => (
        state => ReasonReact.Update({...state, status: Failed})
      )
    | Reset => (state => ReasonReact.Update(emptyState))
    },
  render: ({state, handle, send}) =>
    <div className="section">
      <div> <h2> (ReasonReact.stringToElement("Contact us")) </h2> </div>
      <p> (ReasonReact.stringToElement("6 beers brewing company")) </p>
      <p>
        (
          ReasonReact.stringToElement(
            "Margaritenweg 23, 2384 Breitenfurt Austria",
          )
        )
      </p>
      <p> (ReasonReact.stringToElement("Tel.: +43 677 624 168 66")) </p>
      <form className="needs-validation">
        <fieldset
          disabled=(
            switch (state.status) {
            | Loading => true
            | _ => false
            }
          )>
          (
            switch (state.status) {
            | Idle =>
              <div>
                <div className="row">
                  <div className="col-md-6">
                    <div
                      className=(
                        "form-group"
                        ++ (state.name.isValid ? "" : " has-error")
                      )>
                      <input
                        itemType="text"
                        value=state.name.value
                        placeholder="Name"
                        className="form-control"
                        onBlur=(_event => send(Validate))
                        onChange=(
                          event =>
                            send(
                              ChangeName(
                                ReactDOMRe.domElementToObj(
                                  ReactEventRe.Form.target(event),
                                )##value,
                              ),
                            )
                        )
                      />
                    </div>
                  </div>
                  <div className="col-md-6">
                    <div
                      className=(
                        "form-group"
                        ++ (state.email.isValid ? "" : " has-error")
                      )>
                      <input
                        itemType="email"
                        placeholder="john.doe@email.com"
                        className="form-control"
                        value=state.email.value
                        required=true
                        onBlur=(_event => send(Validate))
                        onChange=(
                          event =>
                            send(
                              ChangeEmail(
                                ReactDOMRe.domElementToObj(
                                  ReactEventRe.Form.target(event),
                                )##value,
                              ),
                            )
                        )
                      />
                    </div>
                  </div>
                </div>
                <div className="row">
                  <div className="col-md-12">
                    <div
                      className=(
                        "form-group"
                        ++ (state.text.isValid ? "" : " has-error")
                      )>
                      <textarea
                        className="form-control"
                        value=state.text.value
                        placeholder="Text"
                        rows=3
                        required=true
                        onBlur=(_event => send(Validate))
                        onChange=(
                          event =>
                            send(
                              ChangeText(
                                ReactDOMRe.domElementToObj(
                                  ReactEventRe.Form.target(event),
                                )##value,
                              ),
                            )
                        )
                      />
                    </div>
                  </div>
                </div>
                <div className="row bottom-margin-l">
                  <div className="col-md-12">
                    <button
                      disabled=(
                        ! state.name.isValid
                        || ! state.email.isValid
                        || ! state.text.isValid
                      )
                      onClick=(_event => send(Submit))
                      className="btn btn-success btn-large btn-block">
                      (ReasonReact.stringToElement("Submit"))
                    </button>
                  </div>
                </div>
              </div>
            | Loading =>
              <div>
                <div className="row">
                  <div className="col-md-6">
                    <input
                      itemType="text"
                      value=state.name.value
                      placeholder="Name"
                      className="form-control"
                      onChange=(
                        event =>
                          send(
                            ChangeName(
                              ReactDOMRe.domElementToObj(
                                ReactEventRe.Form.target(event),
                              )##value,
                            ),
                          )
                      )
                    />
                  </div>
                  <div className="col-md-6">
                    <input
                      itemType="email"
                      placeholder="john.doe@email.com"
                      className="form-control"
                      value=state.email.value
                      required=true
                      onChange=(
                        event =>
                          send(
                            ChangeEmail(
                              ReactDOMRe.domElementToObj(
                                ReactEventRe.Form.target(event),
                              )##value,
                            ),
                          )
                      )
                    />
                  </div>
                </div>
                <div className="row">
                  <div className="col-md-12">
                    <textarea
                      className="form-control"
                      value=state.text.value
                      placeholder="Text"
                      rows=3
                      required=true
                      onChange=(
                        event =>
                          send(
                            ChangeText(
                              ReactDOMRe.domElementToObj(
                                ReactEventRe.Form.target(event),
                              )##value,
                            ),
                          )
                      )
                    />
                  </div>
                </div>
                <div className="row bottom-margin-l">
                  <div className="col-md-12">
                    <button
                      onClick=(_event => send(Submit))
                      className="btn btn-success btn-large btn-block">
                      (ReasonReact.stringToElement("Submit"))
                    </button>
                  </div>
                </div>
              </div>
            | Success =>
              <div className="margin-l">
                <div className="col-md-2">
                  <span className="fui-check-circle" />
                </div>
                <div className="col-md-10">
                  <p>
                    (
                      ReasonReact.stringToElement(
                        "Your question was successfully submitted. You will receive a response in the coming days!",
                      )
                    )
                  </p>
                </div>
                <div className="col-md-12">
                  <button
                    className="btn btn-info btn-large btn-block margin-xl"
                    onClick=(_event => send(Reset))>
                    (ReasonReact.stringToElement("Send another question"))
                  </button>
                </div>
              </div>
            | Failed =>
              <div>
                <span className="fui-cross-circle" />
                <span>
                  (
                    ReasonReact.stringToElement(
                      "The submission failed! Please try again.",
                    )
                  )
                </span>
              </div>
            }
          )
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
        </fieldset>
      </form>
    </div>,
};