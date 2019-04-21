#pragma once

#include <vector>

#include "FrontElement.h"

#define WAVE_DEBUG 1

using namespace my_math;

class Wave {
 public:
  Wave();

  bool Draw() const;

  bool Dump() const;

  bool Push(const FrontElement & front_element);

  virtual ~Wave();

 private:
  std::vector<FrontElement> front_elements_;
};
