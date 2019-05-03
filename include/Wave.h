#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "FrontElement.h"

//#define WAVE_DEBUG 1


/// Modes of drawing waves.
enum DRAWN_SIDES
{	
  TOP_SIDE = 0, ///< Draw only top part of the wave.
  BOTTOM_SIDE = 1, ///< Draw only bottom side of the wave. 
  BOTH_SIDES = 2 ///< Draw both parts of the wave.
};


namespace my_math
{

class Wave {
 public:
  Wave();

  bool Draw(sf::RenderWindow & window);

  bool Dump() const;

  bool Push(const FrontElement & front_element);

  FrontElement & GetMain();

  bool Clear();

  void SetDrawnSides(const DRAWN_SIDES drawn_sides);

  DRAWN_SIDES GetDrawnSides(void) const;

  virtual ~Wave();

 private:
  std::vector<FrontElement> front_elements_;
  DRAWN_SIDES drawn_sides_;
};

} //End of namespace my_math.