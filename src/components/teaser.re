let component = ReasonReact.statelessComponent "Teaser";

/* [%%bs.raw {|
  var React = require('react');
  var Slider = require('react-slick');

  class SimpleSlider extends React.Component {
    render: function () {
      var settings = {
        dots: true,
        infinite: true,
        speed: 500,
        slidesToShow: 1,
        slidesToScroll: 1
      };
      return (
        <Slider {...settings}>
          <div><h3>1</h3></div>
          <div><h3>2</h3></div>
          <div><h3>3</h3></div>
          <div><h3>4</h3></div>
          <div><h3>5</h3></div>
          <div><h3>6</h3></div>
        </Slider>
      );
    }
  }
  |}]; */

let make _children => {
    ...component,
    render: fun _self =>
      <div> </div>
};

/* let make _children => {
  ...component,
  render: fun _self =>
  <div id="carousel-example-generic" className="carousel slide" data-ride="carousel">

    <ol className="carousel-indicators">
      <li data-target="#carousel-example-generic" data-slide-to="0" className="active"> </li>
      <li data-target="#carousel-example-generic" data-slide-to="1"> </li>
      <li data-target="#carousel-example-generic" data-slide-to="2"> </li>
    </ol>

    <div className="carousel-inner" role="listbox">
      <div className="item active">
        <img src="..." alt="..." />
        <div className="carousel-caption">
          (ReasonReact.stringToElement "...")
        </div>
      </div>
      <div className="item">
        <img src="..." alt="..." />
        <div className="carousel-caption">
          (ReasonReact.stringToElement "...")
        </div>
      </div>
      (ReasonReact.stringToElement "...")
    </div>

    <a className="left carousel-control" href="#carousel-example-generic" role="button" data-slide="prev">
      <span className="glyphicon glyphicon-chevron-left" aria-hidden="true"> </span>
      <span className="sr-only"> (ReasonReact.stringToElement "Previous") </span>
    </a>
    <a className="right carousel-control" href="#carousel-example-generic" role="button" data-slide="next">
      <span className="glyphicon glyphicon-chevron-right" aria-hidden="true"> </span>
      <span className="sr-only"> (ReasonReact.stringToElement "Next") </span>
    </a>
  </div>
}; */
