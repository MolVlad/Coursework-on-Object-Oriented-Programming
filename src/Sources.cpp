#include "Sources.h"

#include <chrono>
namespace my_math
{
extern std::chrono::high_resolution_clock::time_point time_start;

sf::Texture dipole_texture_array[NUMBER_DIPOLE_TEXTURES];

bool CreateDipoleTexture(sf::Texture *texture_array) 
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

Source::Source(const Vector2 & position)
    :  Element(position)  {

  phase_ = DEFAULT_PHASE;
  amplitude_ = DEFAULT_AMPLITUDE;
}

Source::Source(void) {
  phase_ = DEFAULT_PHASE;
  amplitude_ = DEFAULT_AMPLITUDE;
}

Source::Source(const Source & that)
    :  Element(that),
       phase_(that.phase_),
       amplitude_(that.amplitude_)  {
}


Source::Source(Source && that)
    :  Element(that),
       phase_(std::move(that.phase_)),
       amplitude_(std::move(that.amplitude_))  {
}


Source::~Source(void) {

}

Vector2 Source::GetFieldStrength(const Vector2 & point, const float t) const
{
}

bool Source::SetPhase(const float phase) {
  phase_ = phase;
}

bool Source::SetAmplitude(const float amplitude) {
  amplitude_ = amplitude;
}

const float Source::GetPhase(void) const {
  return phase_;
}

const float Source::GetAmplitude(void) const {
  return amplitude_;
}

Dipole::Dipole(const Vector2 & position, const int texture_index)
    :  Source(position)  {

  #ifdef TIME_COUNT_DIPOLE
  std::chrono::high_resolution_clock::time_point debag_time_stamp = std::chrono::high_resolution_clock::now();
  #endif

  #ifndef DIPOLE_TEXTURE_WAS_CREATED
  CreateDipoleTexture(dipole_texture_array);
  #define DIPOLE_TEXTURES_WAS_CREATED -6666
  #endif /* DIPOLE_TEXTURE_WAS_CREATED */

  sprite_ = sf::Sprite(dipole_texture_array[texture_index]);
  sprite_.setScale(DIPOLE_SCALE_X, DIPOLE_SCALE_Y);

  const sf::Vector2u dipole_size = sprite_.getTexture( ) -> getSize( );
  sprite_.setOrigin(dipole_size.x / 2, dipole_size.y  / 2);
  sprite_.setPosition(position_.GetX( )  , position_.GetY( ));
  sprite_.setRotation(DEFAULT_DIPOLE_DIRECTION);

  // It is neccesary nearly 0.0155683 for it.
  #ifdef TIME_COUNT_DIPOLE
  std::chrono::duration<float> debag_diff = std::chrono::high_resolution_clock::now() - debag_time_stamp;
  std::cout << debag_diff.count( ) << std::endl; 
  #endif
  return;
}

Dipole::Dipole(const Dipole &that)
    :  Source(that), 
       sprite_(that.sprite_)  {
}


Dipole::Dipole(Dipole &&that)
    :  Source(that),
       sprite_(std::move(that.sprite_))  {
}


bool Dipole::Draw(sf::RenderWindow & window) {
  sprite_.setRotation(direction_);
  window.draw(sprite_);
  return true;
}

Vector2 Dipole::GetFieldStrength(const Vector2 & point, const float t) const
{
  #ifdef TIME_COUNT_GET_FIELD_FROM_SINGULAR
  std::chrono::high_resolution_clock::time_point debag_time_stamp = std::chrono::high_resolution_clock::now();
  #endif

  Vector2 radius_vector = point - position_;
  float distance = radius_vector.Len();


  #ifdef DIPOLE_STRENGTH_DEBUG
  std::cout << "Dipole::GetFieldStrength()" << std::endl;
  std::cout << "\tpoint: " << point << ", dipole: " << position_ << std::endl;
  std::cout << "\t\tradius_vector: " << radius_vector << std::endl;
  std::cout << "\tdistance: " << distance << std::endl;
  #endif /* DIPOLE_STRENGTH_DEBUG */


  if (!distance)
  {
    std::cout << "WARNING:distance = 0 " << std::endl;
    return Vector2(0, 0);
  }

  // cos(angle<p, r>)
  float angular_coefficient = radius_vector.GetCosAngleBetweenVectors(Vector2(1, 0).GetRotated(direction_));

  if(angular_coefficient < 0)
    angular_coefficient *= -1;

  // sin(omega*t + k*r + phase)
  // Last version: sin((CYCLIC_FREQUENCY * (t - distance / (DISTANT_SCALE * LIGHT_SPEED)  + phase_) * ONE_RADIAN)
  float harmonic_part = sin((CYCLIC_FREQUENCY * (t - distance / (DISTANT_SCALE * LIGHT_SPEED))  + phase_) * ONE_RADIAN);


  #ifdef DIPOLE_STRENGTH_DEBUG
  std::cout << "\t\tt: " << t << std::endl;
  std::cout << "\t\tOmega * t: " << CYCLIC_FREQUENCY * t << std::endl;
  std::cout << "\t\tkr: " << CYCLIC_FREQUENCY * (t - distance / (LIGHT_SPEED * DISTANT_SCALE)) << std::endl;
  std::cout << "\t\tphase: " << phase_ << std::endl;
  std::cout << "\tharmonic_part: " << harmonic_part << std::endl;
  #endif /* DIPOLE_STRENGTH_DEBUG */


  Vector2 result = radius_vector.GetRotated(90);
  result.Norm();

  float field_strength = amplitude_ * angular_coefficient * harmonic_part / (distance / DISTANT_SCALE);

  result *= field_strength;

  #ifdef DIPOLE_STRENGTH_DEBUG
  std::cout << "\tE " << field_strength << " Omega*t: " << harmonic_part << " t " << t << std::endl;
  std::cout << "\tamplitude: " << amplitude_ << std::endl;
  std::cout << "\tangular_coefficient: " << angular_coefficient << std::endl;
  std::cout << "\tresult: " << result << " = " << result.Len() << std::endl;
  std::cout << "Dipole::GetFieldStrength() end" << std::endl;
  std::cout << std::endl;
  #endif /* DIPOLE_STRENGTH_DEBUG */

  // It is necessary nearly 1.04e-06 for it.
  #ifdef TIME_COUNT_GET_FIELD_FROM_SINGULAR
  std::chrono::duration<float> debag_diff = std::chrono::high_resolution_clock::now() - debag_time_stamp;
  std::cout << debag_diff.count( ) << std::endl; 
  #endif

  return result;
}


bool Dipole::SetImageScale(const float image_scale)
{
  assert(image_scale > 0);

  sprite_.setScale(DIPOLE_SCALE_X * image_scale, DIPOLE_SCALE_Y * image_scale);
  return true;
}


bool Dipole::SetDirection(const float direction) {
  Element::SetDirection(direction);
  sprite_.setRotation(direction_);
  return true;
}

bool Dipole::SetPosition(const Vector2 & position) {
  Element::SetPosition(position);
  sprite_.setPosition(position.GetX( ), position.GetY( ));
  return true;
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


SecondarySource::SecondarySource(void) 
    :  Source()  {
}


SecondarySource::SecondarySource(const SecondarySource & that)
    :  Source(that),
       field_strength_(that.field_strength_),
       square_(that.square_)  {
}


SecondarySource::SecondarySource(SecondarySource && that)
    :  Source(that),
       field_strength_(std::move(that.field_strength_)),
       square_(std::move(that.square_))  {
}

void SecondarySource::Swap(SecondarySource & that)
{
  std::swap(field_strength_, that.field_strength_);
  std::swap(square_, that.square_);
  std::swap(phase_, that.phase_);
  std::swap(amplitude_, that.amplitude_);
  std::swap(position_, that.position_);
  std::swap(direction_, that.direction_);
  return;

}

SecondarySource & SecondarySource::operator=(const SecondarySource & that)
{
  SecondarySource tmp(that);
  Swap(tmp);
  return *this;  
}

SecondarySource& SecondarySource::operator=(SecondarySource && that)
{
  Swap(that);
  return *this;  
}


SecondarySource::SecondarySource(const Vector2 & position, const float width_secondary_source_area)
    :  Source(position),
       square_(pow(width_secondary_source_area, 2))  {
}

// need to create
bool SecondarySource::Draw(sf::RenderWindow & window)
{

}


bool SecondarySource::Dump() const
{
  #ifdef SECONDARY_SOURCE_DEBUG
  std::cout << "Dipole::Dump()" << std::endl;
  #endif /* DIPOLE_DEBUG */

  std::cout << "Position = " << position_ << std::endl;
  std::cout << "Direction = " << direction_ << std::endl;
  std::cout << "Phase = " << phase_ << std::endl;
  std::cout << "Amplitude = " << amplitude_ << std::endl;


  #ifdef SECONDARY_SOURCE_DEBUG
  std::cout << "Dipole::Dump() end" << std::endl;
  #endif /* DIPOLE_DEBUG */
}


Vector2 SecondarySource::GetFieldStrength(const Vector2 & point, const float t, const std::vector<Dipole> &dipoles_) const
{
  Vector2 base_field_strength = Vector2(0., 0.);
  for (auto& dipole : dipoles_)
  {
    base_field_strength += dipole.GetFieldStrength(position_, t);
  }
  

  Vector2 relative_position = point - position_;
  float relative_distance = relative_position.Len( );
  Vector2 direction = relative_position.GetRotated(90.);
  direction.Norm( );
  Vector2 normal_vector = Vector2(1., 0.);
  
  // cos(kr) * (1 + cos(\alpha)).
  float angular_part = (1 + normal_vector.GetCosAngleBetweenVectors(relative_position)) *
                       cos(WAVE_NUMBER * relative_distance);

  // S / (2 * \lambda * r). S - square.
  float other_part =  square_ / (2 * WAVE_LENGTH * relative_distance);
  Vector2 field_strength = other_part * angular_part * direction * base_field_strength.Len( );

  #ifdef SECONDARY_SOURCE_STRENGTH_DEBAG
  std::cout << "field strength = " << field_strength << std::endl;
  #endif

  return field_strength;
}


SecondarySource::~SecondarySource() {
}

} // End of namespace my_math.