#include "Sources.h"

sf::Texture dipole_texture;

Source::Source(const Vector2 & position)
    :  Element(position)  {
}

Source::Source()
{

}

Source::~Source()
{

}

bool Source::SetPhase(const float phase)
{
  phase_ = phase;
}

bool Source::SetAmplitude(const float amplitude)
{
  amplitude_ = amplitude;
}


Dipole::Dipole(const Vector2 & position)
    :  Source(position)  {

  if (!dipole_texture.loadFromFile("images/dipole_mini.png")) {
    std::cout << "Error of loading texutre:\n" << "file = " << __FILE__ << std::endl 
              <<  "line = " << __LINE__ << std::endl 
              << "function = " << __PRETTY_FUNCTION__ << std::endl;
    exit(-1); 
  }
  sprite_ = sf::Sprite(dipole_texture);
  sprite_.setRotation(direction_);
}

bool Dipole::Draw(sf::RenderWindow & window) {

  sprite_.setPosition(position_.GetX( ), position_.GetY( ));
  window.draw(this -> sprite_);
  return true;
}

// need to create
float Dipole::GetFieldStrength(const Vector2 point) const
{

}

// need to create
bool Dipole::SetImageScale(const float image_scale)
{
  sprite_.setScale(X_SCALE * image_scale, Y_SCALE * image_scale);
  return true;
}

// need to create
bool Dipole::SetImageDirection(const float direction) {
  direction_ = direction;  
}

bool Dipole::Dump() const
{
  #ifdef DIPOLE_DEBUG
  std::cout << "Dipole::Dump()" << std::endl;
  #endif /* DIPOLE_DEBUG */

  std::cout << "\tposition: " << position_ << std::endl;
  std::cout << "\tdirection: " << direction_ << std::endl;
  std::cout << "\tphase: " << phase_ << std::endl;
  std::cout << "\tamplitude: " << amplitude_ << std::endl;

  #ifdef DIPOLE_DEBUG
  std::cout << "Dipole::Dump() end" << std::endl;
  #endif /* DIPOLE_DEBUG */

  std::cout << std::endl;
  return true;
}

Dipole::~Dipole()
{

}

SecondarySource::SecondarySource()
{

}

SecondarySource::SecondarySource(const Vector2 & position)
    :  Source(position)
{

}

// need to create
bool SecondarySource::Draw(sf::RenderWindow & window)
{

}

// need to create
bool SecondarySource::Dump() const
{

}

// need to create
float SecondarySource::GetFieldStrength(const Vector2 point) const
{

}

SecondarySource::~SecondarySource()
{

}
