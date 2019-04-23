#include "Wave.h"

using namespace my_math;

Wave::Wave( ) {

}

bool Wave::Draw(sf::RenderWindow & window) {
  for(auto &i : front_elements_) {
    i.Draw(window);
  }

  return true;
}

bool Wave::Dump( ) const
{
#ifdef WAVE_DEBUG
  std::cout << "Wave::Dump" << std::endl;
#endif /* WAVE_DEBUG */

  for(auto& i : front_elements_)
    i.Dump();

#ifdef WAVE_DEBUG
  std::cout << "Wave::Dump end" << std::endl;
#endif /* WAVE_DEBUG */

  std::cout << std::endl;
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
#endif /* WAVE_DEBUG */

  std::cout << std::endl;
  return true;
}

FrontElement & Wave::GetMain()
{
  return front_elements_.front();
}

bool Wave::IsWaveFarFromCenter()
{
  return (GetMain().GetPosition() - Vector2(DEFAULT_AREA_CENTER_X, DEFAULT_AREA_CENTER_Y)).Len() > MAX_DISTANCE_FROM_AREA_CENTER;
}

Wave::~Wave()
{

}
