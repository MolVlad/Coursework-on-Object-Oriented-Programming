#include"Element.h"

Element::Element(const Vector2 & position)
{
  position_ = position;
  direction_ = DEFAULT_DIPOLE_DIRECTION;
}

Element::Element(const Element & that)
    :  position_(that.position_),
       direction_(that.direction_)  {
}

Element::Element(Element && that)
    :  position_(std::move(that.position_)),
       direction_(std::move(that.direction_))  {
}


Element::~Element()
{

}

Element::Element()
{

}

Vector2 Element::GetPosition() const
{
  return position_;
}

float Element::GetDirection() const
{
  return direction_;
}

bool Element::SetPosition(const Vector2 & position)
{
  position_ = position;

  return true;
}

bool Element::SetDirection(const float direction)
{
  direction_ = direction;

  return true;
}

