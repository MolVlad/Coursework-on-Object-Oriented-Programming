#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "Element.h"

namespace my_math {

const float DEFAULT_AREA_RADIUS = 200.;
const float DEFAULT_AREA_PCOUNT = 40.;

class DipoleArea : public Element {
 public:
  DipoleArea(void); 

  DipoleArea(const DipoleArea & dipole_area) = delete;

  DipoleArea & operator=(const DipoleArea & dipole_area) = delete;

  virtual bool Draw(sf::RenderWindow & window) override;

  virtual bool Dump(void) const override;

 private:
  sf::CircleShape circle_shape_;
};

  bool CreateTexture(void);
}// End of namespace my_math.