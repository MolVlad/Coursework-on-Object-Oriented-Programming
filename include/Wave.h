#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "FrontElement.h"

//#define WAVE_DEBUG 1

using namespace my_math;

class Wave {
 public:
  Wave();

  bool Draw(sf::RenderWindow & window);

  bool Dump() const;

  bool Push(const FrontElement & front_element);

  FrontElement & GetMain();

  bool Clear();

  virtual ~Wave();

 private:
  std::vector<FrontElement> front_elements_;
};
