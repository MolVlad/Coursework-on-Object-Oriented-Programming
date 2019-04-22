#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "Element.h"

namespace my_math {

const float DEFAULT_AREA_SCALE = 0.2;

class DipoleArea : public Element {
 public:
  DipoleArea(void); 

  DipoleArea(const DipoleArea & dipole_area) = delete;

  DipoleArea & operator=(const DipoleArea & dipole_area) = delete;

  virtual bool Draw(sf::RenderWindow & window) override;

  virtual bool Dump(void) const override;

 private:
  Vector2 position_;

  sf::Sprite sprite_;
};

  bool CreateTexture(void);
}// End of namespace my_math.