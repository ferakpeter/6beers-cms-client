let component = ReasonReact.statelessComponent("Header");

let make = _children => {
  ...component,
  render: _self =>
    <nav className="navbar navbar-inverse navbar-fixed-top" role="navigation">
      <div className="container">

          <div className="navbar-header">
            <button id="menu-toggle" className="navbar-toggle" />
            <a className="navbar-brand" href="#">
              (ReasonReact.stringToElement("6 beers brewing co."))
            </a>
          </div>
          <div className="collapse navbar-collapse">
            <ul className="nav navbar-nav navbar-right navbar-uppercase">
              <li className="social-links">
                <a
                  target="_blank"
                  href="https://www.facebook.com/6beersbrewing">
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
        /* <svg xmlns="http://www.w3.org/2000/svg" width="100" height="100">
             <path fill="#F39C12" d="M100 93c0 3.313-2.687 6-6 6h-88c-3.313 0-6-2.687-6-6v-73h100v73z"/>
             <rect x="4" fill="#E57D22" width="92" height="20"/>
             <polygon fill="#F39C12" points="96,20 88,20 88,8 96,0"/>
             <polygon fill="#F39C12" points="4,20 12,20 12,8 4,0"/>
             <polygon fill="#F1C40F" points="12,8 12,20 0,20"/>
             <polygon fill="#F1C40F" points="88,8 88,20 100,20"/>
             <circle opacity=".3" cx="26" cy="40" r="5"/>
             <circle opacity=".3" cx="74" cy="40" r="5"/>
             <path clipRule="evenodd" stroke="#fff" strokeWidth="6" strokeLinecap="round" strokeMiterlimit="10" d="M74 40c0 13.254-10.745 24-24 24s-24-10.745-24-24" fill="none" />
           </svg> */
    </nav>,
};