#include "Wave.h"

using namespace my_math;

Wave::Wave()
{

}

// need to create
bool Wave::Draw(const sf::RenderWindow & window) const
{

}

bool Wave::Dump() const
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

Wave::~Wave()
{

}