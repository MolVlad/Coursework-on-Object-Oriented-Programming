#include"Element.h"

Element::Element(const Vector2 & position)
{
  position_ = position;
}

Element::~Element()
{

}

// need to create
bool Element::Draw() const
{

  return true;
}

// need to create
bool Element::Dump() const
{

  return true;
}

Vector2 Element::GetPosition() const
{
  return position_;
}

Vector2 Element::GetDirection() const
{
  return direction_;
}

bool Element::SetPosition(const Vector2 & position)
{
  position_ = position;

  return true;
}

bool Element::SetDirection(const Vector2 & direction)
{
  direction_ = direction;

  return true;
}


