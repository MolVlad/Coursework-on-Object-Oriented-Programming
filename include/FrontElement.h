#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "Element.h"

#define FRONT_ELEMENT_DEBUG 1

#define FRONT_ELEMENT_DEBUG 1

using namespace my_math;

const float DEFAULT_RADIUS = 3.;
const float DEFAULT_POINT_COUNT = 40.;

class FrontElement : public Element {
 public:
  FrontElement();

  explicit FrontElement(const Vector2 & position);

  bool Draw(sf::RenderWindow & window) override;

  // Draw a small ball. All these balls create wave front.
  bool Dump() const override;

  float GetAmplitude() const;

  bool SetAmplitude(const float amplitude);

  virtual ~FrontElement();

 private:
  float amplitude_;
  sf::CircleShape circle_shape_;
};
