open Jest;

open ExpectJs;

let _ =
  describe
    "src/app.re"
    (
      fun _ => {
        test
          "is defined"
          (
            fun () => {
              let component = ReactShallowRenderer.renderWithRenderer <App />;
              expect (Js.Undefined.return component) |> toBeDefined
            }
          );
        test
          "renders"
          (
            fun _ => {
              let tree = <App /> |> ReactShallowRenderer.renderWithRenderer;
              expect tree |> toMatchSnapshot
            }
          )
      }
    );
