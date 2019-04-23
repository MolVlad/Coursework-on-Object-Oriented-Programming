#pragma once

#include<vector>
#include <SFML/Graphics.hpp>

#include "Wave.h"
#include "Sources.h"
#include "DipoleArea.h"

#define STORE_DEBUG 1

const float MOVE_SPEED = 1;

const float CENTER_X = 0;
const float CENTER_Y = 300;

class Store {
 public:
  Store();

  bool Push(const Dipole & dipole);

  bool Push(const Wave & wave);

  bool Draw(sf::RenderWindow & window);

  bool Dump() const;

  //Move waves along vector k by c*t
  bool MoveWaves();

  Vector2 GetFieldStrength(const my_math::Vector2 & position) const;

  ~Store();

 private:
  std::vector<Dipole> dipoles_;
  std::vector<Wave> waves_;
  DipoleArea dipole_area_;
};
