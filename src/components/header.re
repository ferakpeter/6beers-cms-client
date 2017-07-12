let component = ReasonReact.statelessComponent "Header";

let make _children => {
  ...component,
  render: fun _self =>
    <nav className="navbar navbar-inverse navbar-fixed-top" role="navigation">
    <div className="container">
      <div className="navbar-header">
          <button id="menu-toggle" className="navbar-toggle">

          </button>
          <a className="navbar-brand" href="#"> (ReasonReact.stringToElement "6 beers brewing co.") </a>
      </div>
      <div className="collapse navbar-collapse">
        <ul className="nav navbar-nav navbar-right navbar-uppercase">
          <li className="social-links">
              <a href="https://www.facebook.com/6beersbrewing">
                  <span className="fui-facebook"> </span>
              </a>
              <a href="https://instagram.com/6beersbrewing">
                  <span className="fui-instagram"> </span>
              </a>
          </li>
          <li>
              <a href="#/brewery">
              (ReasonReact.stringToElement "Brewery")
              </a>
          </li>
          <li>
              <a href="#/beer">
              (ReasonReact.stringToElement "Beer")
              </a>
          </li>
          <li>
              <a href="#/order">
              (ReasonReact.stringToElement "Make an Order")
              </a>
          </li>
          <li>
              <a href="#/contact">
              (ReasonReact.stringToElement "Contact Us")
              </a>
          </li>
        </ul>
      </div>
    </div>
    </nav>
};
