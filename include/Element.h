#pragma once

#include <SFML/Graphics.hpp>

#include"Vector2.h"

using namespace my_math;

const float DEFAULT_DIRECTION = 0.;

class Element {
 public:
  Element();

  explicit Element(const Vector2 & position);

  virtual bool Draw(sf::RenderWindow & window) = 0;

  virtual bool Dump() const = 0;

  Vector2 GetPosition() const;

  float GetDirection() const;

  bool SetPosition(const Vector2 & position);

  bool SetDirection(const float direction);

  virtual ~Element();

 protected:
  Vector2 position_;
  float direction_;
  sf::Sprite sprite_;
};