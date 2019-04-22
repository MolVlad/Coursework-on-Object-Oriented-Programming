#include"FrontElement.h"

sf::Texture front_element_texture;

FrontElement::FrontElement()
{

}

FrontElement::FrontElement(const Vector2 & position)
    :  Element(position)
{
  circle_shape_ = sf::CircleShape(DEFAULT_RADIUS, DEFAULT_POINT_COUNT);
  circle_shape_.setFillColor(sf::Color::Red);
}

FrontElement::~FrontElement()
{

}


bool FrontElement::Draw(sf::RenderWindow & window)
{
  circle_shape_.setPosition(position_.GetX( ), position_.GetY( ));
  window.draw(circle_shape_);
  return true;
}

bool FrontElement::Dump() const
{
  #ifdef FRONT_ELEMENT_DEBUG
  std::cout << "FrontElement::Dump()" << std::endl;
  #endif /* FRONT_ELEMENT_DEBUG */

  std::cout << "\tposition: " << position_ << std::endl;
  std::cout << "\tdirection: " << direction_ << std::endl;
  std::cout << "\tamplitude: " << amplitude_ << std::endl;

  #ifdef FRONT_ELEMENT_DEBUG
  std::cout << "FrontElement::Dump() end" << std::endl;
  #endif /* FRONT_ELEMENT_DEBUG */

  std::cout << std::endl;
  return true;
}

float FrontElement::GetAmplitude() const
{
  return amplitude_;
}

bool FrontElement::SetAmplitude(float amplitude)
{
  amplitude_ = amplitude;

  return true;
}
