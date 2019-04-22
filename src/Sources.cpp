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

  phase_ = DEFAULT_PHASE;
  amplitude_ = DEFAULT_AMPLITUDE;
}

Source::Source()
{
  phase_ = DEFAULT_PHASE;
  amplitude_ = DEFAULT_AMPLITUDE;
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

// need to finish
float Dipole::GetFieldStrength(const Vector2 & point) const
{
  Vector2 radius_vector = point - position_;
  float distance = radius_vector.Len();

  #ifdef DIPOLE_DEBUG
  std::cout << "Dipole::GetFieldStrength()" << std::endl;

 std::cout << "\tpoint: " << point << ", dipole: " << position_ << std::endl;
  std::cout << "\tradius_vector: " << radius_vector << std::endl;
  std::cout << "\tdistance: " << distance << std::endl;
  #endif /* DIPOLE_DEBUG */

  if(!distance)
    return 0;

  // cos(angle<p, r>)
  float angular_coefficient = 1;  //cos();

  // sin(omega*t + k*r + phase)
  float harmonic_part = 1;  //sin(CYCLIC_FREQUENCY);

  float result = amplitude_ * angular_coefficient * harmonic_part / distance;

  #ifdef DIPOLE_DEBUG
  std::cout << "\tamplitude: " << amplitude_ << std::endl;
  std::cout << "\tangular_coefficient: " << angular_coefficient << std::endl;
  std::cout << "\tharmonic_part: " << harmonic_part << std::endl;
  std::cout << "\tresult: " << result << std::endl;
  std::cout << "Dipole::GetFieldStrength() end" << std::endl;
  std::cout << std::endl;
  #endif /* DIPOLE_DEBUG */

  return result;
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
float SecondarySource::GetFieldStrength(const Vector2 & point) const
{

}

SecondarySource::~SecondarySource()
{

}
