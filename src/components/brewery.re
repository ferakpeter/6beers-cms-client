let component = ReasonReact.statelessComponent "Brewery";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="section section-we-do-2" id="brewery">
          <div className="container">
              <div className="row">
                  <h2> (ReasonReact.stringToElement "Craft brewery") </h2>
                    <img className="img-rounded img-responsive" src="assets/img/mentality.jpg" />
              </div>
              <div className="row">
                <br />
              </div>
              <div className="row">
                  <div className="col-md-4">
                      <div className="card">
                          /* <div className="icon">
                            <img className="img-rounded img-responsive center-block" src="assets/img/icons/png/ingredients.png" />
                              <i className="pe-7s-gift"> </i>
                          </div> */
                          <h3> (ReasonReact.stringToElement "Best Ingredients") </h3>
                          <p> (ReasonReact.stringToElement "According to craft beer brewing tradition we use only the best quality ingredients. We rely mostly on traditional ingredients like water, malt, hops and yeast but include a wide range of additional natural ingredients that produce unique and interesting tastes. We do not have our own brewery, but use the equipment of several midget- and micro-breweries in Austria and Slovakia.") </p>
                      </div>
                  </div>
                  <div className="col-md-4">
                      <div className="card">
                          /* <div className="icon">
                          <img className="img-rounded img-responsive center-block" src="assets/img/icons/png/brewing.png" />
                              <i className="pe-7s-rocket"> </i>
                          </div> */
                          <h3> (ReasonReact.stringToElement "High Quality") </h3>
                          <p> (ReasonReact.stringToElement "Quality is a must and throughout the entire production of our beer we make sure of high quality standards. Besides the wonderful and tasty spring water from the Austrian mountains we rely on premium quality malts from Austria, Slovakia, Czech Republic, Germany and the U.K. Traditional and 'new world' hops from around the world and most reliable and proven yeast strains available.") </p>
                      </div>
                  </div>
                  <div className="col-md-4">
                      <div className="card">
                          /* <div className="icon">
                            <img className="img-rounded img-responsive center-block" src="assets/img/icons/png/glass.png" />
                              <i className="pe-7s-tools"> </i>
                          </div> */
                          <h3> (ReasonReact.stringToElement "Creative Taste") </h3>
                          <p> (ReasonReact.stringToElement "Our beer styles are brewed using the best recipes we collected over years of brewing Craft beer. This way we can use the advantages of the respective equipment to maximize the aromatic profile of our beers. We believe it is not enough to produce a crisp and refreshing beer. We go a step further to bring you an interesting and delicate tasting, enjoyable, high-quality and sometimes challenging drinking experience.") </p>
                      </div>
                  </div>
              </div>
          </div>
      </div>
  };
