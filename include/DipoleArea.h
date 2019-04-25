#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "Element.h"

namespace my_math {

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

}// End of namespace my_math.
