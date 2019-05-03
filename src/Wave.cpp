#include "Wave.h"

namespace my_math
{

Wave::Wave( )
    :  drawn_sides_(BOTH_SIDES) { 
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

Wave::~Wave()
{

}

}  //End of namespace my_math.