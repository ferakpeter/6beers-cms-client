let component = ReasonReact.statelessComponent("Header");

let make = _children => {
  ...component,
  render: _self =>
    <nav className="navbar navbar-inverse navbar-fixed-top" role="navigation">
      <div className="container">
        <div className="navbar-header">
          <button id="menu-toggle" className="navbar-toggle" />
          <a className="navbar-brand" href="#">
            (ReasonReact.stringToElement("Shop"))
          </a>
        </div>
        <div className="collapse navbar-collapse">
          <ul className="nav navbar-nav navbar-right navbar-uppercase">
            <li className="social-links">
              <a target="_blank" href="https://www.facebook.com/6beersbrewing">
                <span className="fui-facebook" />
              </a>
              <a target="_blank" href="https://instagram.com/6beersbrewing">
                <span className="fui-instagram" />
              </a>
            </li>
            <li>
              <a href="#brewery">
                (ReasonReact.stringToElement("Brewery"))
              </a>
            </li>
            <li>
              <a href="#beer"> (ReasonReact.stringToElement("Beer")) </a>
            </li>
            <li>
              <a href="#aboutus">
                (ReasonReact.stringToElement("About Us"))
              </a>
            </li>
            <li>
              <a href="#contact">
                (ReasonReact.stringToElement("Contact Us"))
              </a>
            </li>
          </ul>
        </div>
      </div>
    </nav>,
};