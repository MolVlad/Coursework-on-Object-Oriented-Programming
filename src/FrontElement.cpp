#include"FrontElement.h"

FrontElement::FrontElement()
{

}

FrontElement::FrontElement(const Vector2 & position)
    :  Element(position)
{
  circle_shape_ = sf::CircleShape(DEFAULT_FRONT_ELEMENT_RADIUS, DEFAULT_FRONT_ELEMENT_PCOUNT);
  circle_shape_.setFillColor(sf::Color(255, 0, 0, 255));
}

FrontElement::~FrontElement()
{

}

bool FrontElement::SetRGBA(int R, int G, int B, int A)
{
  circle_shape_.setFillColor(sf::Color(R, G, B, A));
}

bool FrontElement::Draw(sf::RenderWindow & window)
{
  circle_shape_.setPosition(position_.GetX( ), position_.GetY( ));
  window.draw(circle_shape_);

  return true;
}

bool FrontElement::DrawColor(sf::RenderWindow & window, int strength)
{
  circle_shape_.setPosition(position_.GetX( ), position_.GetY( ));
  SetRGBA(255, 0, 0, strength);
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

bool FrontElement::IsFarFromCenter()
{
  return (GetPosition() - Vector2(DEFAULT_AREA_CENTER_X, DEFAULT_AREA_CENTER_Y)).Len() > MAX_DISTANCE_FROM_AREA_CENTER;
}

bool FrontElement::IsOnScreen()
{
  Vector2 position = GetPosition();
  float x, y;
  x = position.GetX();
  y = position.GetY();

  return !((x < 0) || (x > SCREEN_WIDTH) || (y < 0) || (y > SCREEN_HEIGHT));
}
