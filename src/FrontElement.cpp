#include "FrontElement.h"

namespace my_math
{

FrontElement::FrontElement()
{

}


FrontElement::FrontElement(const Vector2 & position)
    :  Element(position)
{
  circle_shape_ = sf::CircleShape(DEFAULT_FRONT_ELEMENT_RADIUS, DEFAULT_FRONT_ELEMENT_PCOUNT);
  circle_shape_.setFillColor(sf::Color(255, 0, 0, 255));
}


FrontElement::FrontElement(const FrontElement &that)
    :  Element(that),
       amplitude_(that.amplitude_),
       circle_shape_(that.circle_shape_)  {
}


FrontElement::FrontElement(FrontElement &&that)
    :  Element(that),
       amplitude_(std::move(that.amplitude_)),
       circle_shape_(std::move(that.circle_shape_))  {
}

void FrontElement::Swap(FrontElement & that)
{
  float tmp_amplitude = amplitude_;
  amplitude_ = that.amplitude_;
  that.amplitude_ = amplitude_;

  sf::CircleShape tmp_circle_shape = that.circle_shape_;
  circle_shape_ = that.circle_shape_;
  that.circle_shape_ = circle_shape_;

  Vector2 tmp_position = that.position_;
  that.position_ = position_;
  position_ = tmp_position;

  float tmp_direction = that.direction_;
  that.direction_ = direction_;
  direction_ = tmp_direction;
  return;
}

FrontElement& FrontElement::operator=(const FrontElement &that)
{
  if (&that == this)
  {
    return *this;
  }
  FrontElement tmp(that);
  Swap(tmp);
  return *this;
}


FrontElement& FrontElement::operator=(FrontElement &&that)
{
  Swap(that);
  return *this;
}

FrontElement::~FrontElement()
{

}

bool FrontElement::SetRGBA(int R, int G, int B, int A)
{
  circle_shape_.setFillColor(sf::Color(R, G, B, A));
}

bool FrontElement::Draw(sf::RenderWindow & window)
{
  circle_shape_.setPosition(position_.GetX( ), position_.GetY( ));
  window.draw(circle_shape_);

  return true;
}

bool FrontElement::DrawColor(sf::RenderWindow & window, float strength)
{
  circle_shape_.setPosition(position_.GetX( ), position_.GetY( ));

  static float upper_bound = 10;
  float rate = strength;
  /*
  if((strength / upper_bound) > 1)
    upper_bound = strength;
    */

  if((rate / upper_bound) > 1)
    upper_bound = rate;

  #ifdef FRONT_ELEMENT_DEBUG
  //std::cout << "FrontElement::DrawColor(). strength: " << strength << " upper_bound: " << upper_bound << std::endl;
  std::cout << "FrontElement::DrawColor(). strength: " << strength << " rate " << rate << " upper_bound: " << upper_bound << std::endl;
  #endif /* FRONT_ELEMENT_DEBUG */

  //SetRGBA(255, 0, 0, (int)((strength / upper_bound) * 255));
  SetRGBA(255, 0, 0, (int)((rate / upper_bound) * 255));
  window.draw(circle_shape_);

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

bool FrontElement::IsFarFromCenter(const WAVE_STATUSES wave_status, const DRAWN_SIDES drawn_sides) const
{
  Vector2 position = GetPosition( );
  bool x_magnitude_statement = (position - Vector2(DEFAULT_AREA_CENTER_X, DEFAULT_AREA_CENTER_Y)).Len() >
                              MAX_DISTANCE_FROM_AREA_CENTER;
  

  bool y_magnitude_statement = false;
  if (!(wave_status == ORDINARY_WAVE && drawn_sides == BOTH_SIDES))  
  {             
    y_magnitude_statement = position.GetY( ) < 0. || position.GetY( ) > SCREEN_HEIGHT;
  }

  return x_magnitude_statement || y_magnitude_statement;
}

bool FrontElement::IsOnScreen(const DiffractionGrating *diffraction_grating) const
{
  Vector2 position = GetPosition();
  float x = position.GetX();
  float y = position.GetY();

  bool light_statement = !((x < DEFAULT_AREA_RADIUS) || (x > SCREEN_WIDTH) || (y < 0) || (y > SCREEN_HEIGHT));

  if (!diffraction_grating)
  {
    return light_statement;
  }
  else
  {
    return light_statement && x > (*diffraction_grating).Right( );
  }
}

} // End of namespace my_math.