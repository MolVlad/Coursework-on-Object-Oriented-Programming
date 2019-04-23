#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>

#include "Vector2.h"

using namespace my_math;

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
const float DEFAULT_DIRECTION = 180;

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

bool CreateTexture(const char* picture, sf::Texture & texture);
