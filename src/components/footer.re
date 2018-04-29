let component = ReasonReact.statelessComponent("Footer");

let make = _children => {
  ...component,
  render: _self =>
    <footer className="footer footer-color-black fixed-bottom">
      <div className="container">
        <nav className="pull-left">
          <ul>
            <li> <a href="#"> (ReasonReact.stringToElement("Home")) </a> </li>
            <li>
              <a href="terms.html" target="_blank">
                
              (ReasonReact.stringToElement("Terms & Conditions"))
              </a>
            </li>
          </ul>
        </nav>
        <div className="social-area pull-right">
          <a
            target="_blank"
            className="btn btn-social btn-facebook btn-simple"
            href="https://www.facebook.com/6beersbrewing">
            <span className="fui-facebook" />
          </a>
          <a
            target="_blank"
            className="btn btn-social btn-instagram btn-simple"
            href="https://instagram.com/6beersbrewing">
            <span className="fui-instagram" />
          </a>
        </div>
        <div className="copyright">
          (ReasonReact.stringToElement("Copyright 2017 "))
          <a target="_blank" href="http://www.6beers.at">
            (ReasonReact.stringToElement("6 beers brewing co."))
          </a>
        </div>
      </div>
    </footer>,
};
