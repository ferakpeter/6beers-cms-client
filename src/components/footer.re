let component = ReasonReact.statelessComponent "Footer";

let make _children => {
  ...component,
  render: fun _self =>
  <footer className="footer footer-color-black">
      <div className="container">
          <nav className="pull-left">
              <ul>
                  <li>
                      <a href="#">
                      (ReasonReact.stringToElement "Home")
                      </a>
                  </li>
                  <li>
                      <a href="terms.html" target="_blank">
                      (ReasonReact.stringToElement "Terms & Conditions")
                      </a>
                  </li>
              </ul>
          </nav>
          <div className="social-area pull-right">
              <a className="btn btn-social btn-facebook btn-simple" href="https://www.facebook.com/6beersbrewing">
                  <span className="fui-facebook"> </span>
              </a>
              <a className="btn btn-social btn-instagram btn-simple" href="https://instagram.com/6beersbrewing">
                  <span className="fui-instagram"> </span>
              </a>
          </div>
          <div className="copyright">
              (ReasonReact.stringToElement "Copyright 2017 ") <a target="_blank" href="http://www.6beers.at"> (ReasonReact.stringToElement "6 beers brewing co.") </a>
          </div>
      </div>
  </footer>
};
