#pragma once

#include <SFML/Graphics.hpp>

#include"Vector2.h"

using namespace my_math;

class Element {
 public:
  Element();

  explicit Element(const Vector2 & position);

  virtual bool Draw(const sf::RenderWindow & window) const = 0;

  virtual bool Dump() const = 0;

  Vector2 GetPosition() const;

  Vector2 GetDirection() const;

  bool SetPosition(const Vector2 & position);

  bool SetDirection(const Vector2 & direction);

  virtual ~Element();

 protected:
  Vector2 position_;
  Vector2 direction_;
  sf::Sprite sprite_;
};