#include"FrontElement.h"

FrontElement::FrontElement()
{

}

FrontElement::FrontElement(const Vector2 & position)
    :  Element(position)
{

}

FrontElement::~FrontElement()
{

}

// need to create
bool FrontElement::Draw(sf::RenderWindow & window) const
{

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
