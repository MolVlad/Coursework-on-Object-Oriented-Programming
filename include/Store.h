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
//#define DRAW_STEP_BY_STEP 1

class Store {
 public:
  Store();

  bool Push(const Dipole & dipole);

  bool Push(const Wave & wave);

  bool Draw(sf::RenderWindow & window);

  bool Dump() const;

  /** 
    \breif Move waves along vector k by c * t / DISTANT_SCALE.
    \return False - There are no dipoles. 
    \return True - At least one dipole exists.
  */
  bool MoveWaves();

  /**
    \brief Removes waves that go beyond the screen. .
    \return Value with no sense.
  */
  bool RemoveDistantWaves();

  /**
    \brief Clear vectors with dipoles and waves. .
    \return Value with no sense.
  */
  bool Clear();

  /**
    \brief Calculate field in this point.
    \param[in] position - Point where field strength should be calculated.
    \return Vector E in this point.
  */
  Vector2 GetFieldStrength(const my_math::Vector2 & position) const;

  ~Store();

 private:
  std::vector<Dipole> dipoles_;
  std::vector<Wave> waves_;
  DipoleArea dipole_area_;
  float time_;

  /**
    \brief Move one wave.
    \param[in] Wave to move it on c * t / DISTANT_SCALE.  .
    \return Value with no sense.
  */
  bool MoveWave(Wave & wave);
};
