#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Wave.h"
#include "Sources.h"
#include "DipoleArea.h"
#include "DiffractionGrating.h"

//#define STORE_DEBUG 1
//#define STORE_DRAW_DEBUG 1
//#define STORE_MOVE_DEBUG 1
//#define STOP_WAVES 1
#define DRAW_ALL_FRONT_ELEMENTS 1
//#define DRAW_STEP_BY_STEP 1

class Store {
 public:
  Store();

  bool Push(const Dipole & dipole);

  bool Push(const Wave & wave);

  bool Push(const DiffractionGrating & diffraction_grating);

  bool Draw(sf::RenderWindow & window);

  bool DrawHalfWave(sf::RenderWindow & window, const Vector2 & main_front_element_position, const bool is_positive_part);

  bool HandleWave(sf::RenderWindow & window, Wave &wave);

  bool Dump() const;

  //Move waves along vector k by c*t
  bool MoveWaves();

  float GetTime();

  bool UpdateTime();

  bool RemoveDistantWaves();

  bool Clear();

  Vector2 GetFieldStrength(const my_math::Vector2 & position) const;

  ~Store();

 private:
  std::vector<Dipole> dipoles_;
  std::vector<Wave> waves_;
  std::vector<DiffractionGrating> diffraction_gratings_;
  DipoleArea dipole_area_;
  float t;
  float time_from_start;

  bool MoveWave(Wave & wave);
};