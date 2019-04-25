#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Wave.h"
#include "Sources.h"
#include "DipoleArea.h"

//#define STORE_DEBUG 1
//#define STORE_DRAW_DEBUG 1
//#define STORE_MOVE_DEBUG 1
//#define STOP_WAVES 1
#define DRAW_ALL_FRONT_ELEMENTS 1

class Store {
 public:
  Store();

  bool Push(const Dipole & dipole);

  bool Push(const Wave & wave);

  bool Draw(sf::RenderWindow & window);

  bool Dump() const;

  //Move waves along vector k by c*t
  bool MoveWaves();

  float GetTime();

  bool UpdateTime();

  bool RemoveDistantWaves();

  Vector2 GetFieldStrength(const my_math::Vector2 & position) const;

  ~Store();

 private:
  std::vector<Dipole> dipoles_;
  std::vector<Wave> waves_;
  DipoleArea dipole_area_;
  float t;

  bool MoveWave(Wave & wave);
};
