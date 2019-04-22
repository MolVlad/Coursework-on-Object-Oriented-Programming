#include"Element.h"

Element::Element(const Vector2 & position)
{
  position_ = position;
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

