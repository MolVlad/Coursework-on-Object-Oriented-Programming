#include"Element.h"

bool CreateTexture(sf::Texture *texture_array) 
{
  assert(texture_array != nullptr);

  for (int ind = 0; ind < NUMBER_DIPOLE_TEXTURES; ind++)
  {
    if (!texture_array[ind].loadFromFile(IMAGE_ARRAY[ind])) {
      std::cout << "Error of loading texutre number " << ind + 1 << ":\n";
      std::cout << "In file = " << __FILE__ << std::endl; 
      std::cout << "In line = " << __LINE__ << std::endl; 
      std::cout << "In function = " << __PRETTY_FUNCTION__ << std::endl;
      exit(-1); 
    }
  }    
  return true;
}

Element::Element(const Vector2 & position)
{
  position_ = position;
  direction_ = DEFAULT_DIPOLE_DIRECTION;
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

