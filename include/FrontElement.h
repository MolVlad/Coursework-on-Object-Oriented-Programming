#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "Element.h"

//#define FRONT_ELEMENT_DEBUG 1

using namespace my_math;

class FrontElement : public Element {
 public:
  FrontElement();

  explicit FrontElement(const Vector2 & position);

  bool Draw(sf::RenderWindow & window) override;

  bool DrawColor(sf::RenderWindow & window, float strength);

  bool Dump() const override;

  float GetAmplitude() const;

  bool SetAmplitude(const float amplitude);

  bool IsFarFromCenter();

  bool IsOnScreen();

  bool SetRGBA(int R, int G, int B, int A);

  virtual ~FrontElement();

 private:
  float amplitude_;
  sf::CircleShape circle_shape_;
};
