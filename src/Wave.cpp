#include "Wave.h"

namespace my_math
{

Wave::Wave( )
    :  drawn_sides_(BOTH_SIDES),
       wave_status_(ORDINARY_WAVE),
       diffraction_grating_(nullptr)  { 
}


Wave::Wave(const Wave &that)  
    :  front_elements_(that.front_elements_),
       drawn_sides_(that.drawn_sides_),
       wave_status_(that.wave_status_),
       diffraction_grating_(that.diffraction_grating_),
       secondary_source_number_(that.secondary_source_number_)  {
}


Wave::Wave(Wave &&that)
    :  front_elements_(std::move(that.front_elements_)),
       drawn_sides_(std::move(that.drawn_sides_)),
       wave_status_(std::move(that.wave_status_)),
       diffraction_grating_(std::move(that.diffraction_grating_)),
       secondary_source_number_(std::move(that.secondary_source_number_))  {
}

void Wave::Swap(Wave & that)
{
  std::swap(front_elements_, that.front_elements_);
  std::swap(drawn_sides_, that.drawn_sides_);
  std::swap(wave_status_, that.wave_status_);
  std::swap(diffraction_grating_, that.diffraction_grating_);
  std::swap(secondary_source_number_, that.secondary_source_number_);
  return;
}


Wave& Wave::operator=(const Wave & that)
{
  Wave tmp(that);
  Swap(tmp);
  return *this;
}

Wave& Wave::operator=(Wave && that)
{
  Swap(that);
  return *this;  
}

bool Wave::Draw(sf::RenderWindow & window) {
  FrontElement &front_element = GetMain();

  front_element.Draw(window);

  return true;
}

bool Wave::Dump( ) const
{
  #ifdef WAVE_DEBUG
  std::cout << "Wave::Dump" << std::endl;
  #endif /* WAVE_DEBUG */

  for(auto& i : front_elements_)
    i.Dump();
  std::cout << "Drawn_sides = " << drawn_sides_ << std::endl;

  #ifdef WAVE_DEBUG
  std::cout << "Wave::Dump end" << std::endl;
  std::cout << std::endl;
  #endif /* WAVE_DEBUG */

  return true;
}

bool Wave::Push(const FrontElement & front_element)
{
  #ifdef WAVE_DEBUG
  std::cout << "Wave::Push(front_element)" << std::endl;
  #endif /* WAVE_DEBUG */

  front_elements_.push_back(front_element);

  #ifdef WAVE_DEBUG
  std::cout << "Wave::Push(front_element) end" << std::endl;
  std::cout << std::endl;
  #endif /* WAVE_DEBUG */

  return true;
}

FrontElement & Wave::GetMain()
{
  return front_elements_.front();
}

bool Wave::Clear()
{
  front_elements_.clear();
}

void Wave::SetDrawnSides(const DRAWN_SIDES drawn_sides)
{
  drawn_sides_ = drawn_sides;
  return;
}

DRAWN_SIDES Wave::GetDrawnSides(void) const
{
  return drawn_sides_;
}

void Wave::SetWaveStatus(const WAVE_STATUSES wave_status)
{
  wave_status_ = wave_status;
  return;
}

const WAVE_STATUSES Wave::GetWaveStatus(void) const
{
  return wave_status_;
}

void Wave::SetDiffractionGrating(DiffractionGrating *diffraction_grating)
{
  diffraction_grating_ = diffraction_grating;
  return;
}

DiffractionGrating* Wave::GetDiffractionGrating(void) const
{
  return diffraction_grating_;
}

void Wave::SetSecondarySourceNumber(const int source_number)
{
  secondary_source_number_ = source_number;
}

int Wave::GetSecondarySourceNumber(void) const
{
  return secondary_source_number_;
}

bool Wave::IsInterfere(void)
{
  if (GetMain( ).GetPosition( ).GetX( ) - (*diffraction_grating_).Right( ) > INTERFERENCE_LENGTH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

Wave::~Wave()
{

}

}  //End of namespace my_math.