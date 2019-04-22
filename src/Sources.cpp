#include "Sources.h"

sf::Texture dipole_texture;

Source::Source(const Vector2 & position)
    :  Element(position)  {

  if (!dipole_texture.loadFromFile("images/dipole.png")) {
    std::cout << "Error of loading texutre:\n" << "file = " << __FILE__ << std::endl 
              <<  "line = " << __LINE__ << std::endl 
              << "function = " << __PRETTY_FUNCTION__ << std::endl;
  exit(-1); 
  }
  sprite_ = sf::Sprite(dipole_texture);
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
    :  Source(position)
{

}

// need to create
bool Dipole::Draw(const sf::RenderWindow & window) const
{
    
}

// need to create
float Dipole::GetFieldStrength(const Vector2 point) const
{

}

// need to create
bool Dipole::SetImageScale(const float image_scale)
{

}

// need to create
bool Dipole::SetImageDirection()
{

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
bool SecondarySource::Draw(const sf::RenderWindow & window) const
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
