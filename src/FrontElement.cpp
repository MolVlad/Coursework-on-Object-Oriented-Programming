#include"FrontElement.h"

FrontElement::FrontElement(const Vector2 & position)
    :  Element(position)
{

}

FrontElement::~FrontElement()
{

}

// need to create
bool FrontElement::Draw() const
{

  return true;
}

// need to test
bool FrontElement::Dump() const
{
  std::cout << "FrontElement Dump" << std::endl;
  std::cout << "position: " << position_ << std::endl;
  std::cout << "direction: " << direction_ << std::endl;
  std::cout << "amplitude: " << amplitude_ << std::endl;
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
