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
#define USING_DIFFRACTION_GRATING 1
#define DRAW_ALL_FRONT_ELEMENTS 1
//#define MEMORY_LEAKS_DEBUG 1
//#define COLLISION_DEBAG 1
//#define DRAW_STEP_BY_STEP 1

class Store {
 public:
  Store();

  bool Push(const Dipole & dipole);

  bool Push(const Wave & wave);

  bool Push(const DiffractionGrating & diffraction_grating);

  bool Draw(sf::RenderWindow & window);

  bool Dump() const;

  //Move waves along vector k by c*t
  bool MoveWaves();

  float GetTime();

  bool UpdateTime();

  bool RemoveDistantWaves();

  bool Clear();

  Vector2 GetFieldStrength(const my_math::Vector2 & position, const DiffractionGrating *diffraction_grating = nullptr) const;

  ~Store();

 private:
  std::vector<Dipole> dipoles_;
  std::vector<Wave> waves_;
  std::vector<DiffractionGrating> diffraction_gratings_;
  DipoleArea dipole_area_;

  float t;
  float time_from_start;

  bool MoveWave(Wave & wave);


  /**
    \breif Handle all waves' collisions with diffraction gratings and draw all waves.
    \param[in] window - Window to draw all waves.
    \return True - Collisions weren't happened, False - collisions were happened. 
  */
  bool HandleAllWaves(sf::RenderWindow & window);


  /**
      \breif Check front element on collisions with difraction gratings.
      \param[in] front_element - Front element to check collisions.
      \return True - Collision wasn't happened. False - Collision was happened.
  */
  bool CheckCollisions(const FrontElement & front_element, const WAVE_STATUSES wave_status);


  /**
      \breif Draw a part of wave.
      \param[out] window - Window to draw wave.
      \param[in] main_front_element_position - Start position to draw.
      \param[in] wave_ind - Index wave in waves_.
      \return Value with no sense.
  */
  bool DrawHalfWave(sf::RenderWindow & window, const Vector2 & main_front_element_position, const bool is_top_part,
                    const int wave_ind);


  /**
      \breif It necessary to split wave. Push one of splited wave's parts in waves_.
      \param[in] position - Position to create new part of wave.
      \param[in] direction - Direction of wave's main front element.
      \param[in] factor - It is 1 if you want to create top part of wave and (-1) if you want to create bottom part.
  */
  void PushWaveMainElement(const Vector2 & position, Vector2 & direction, const signed char factor);


  /**
      \breif Draw wave and check it on collisions.
      \param[out] window - Window to draw wave.
      \param[out] wave - Wave to draw it on window.
      \param[in] wave_ind - Index wave in waves_.
      \return False - Collision with difraction gratings was happened. True - it wasn't happened.
  */ 
  bool HandleWave(sf::RenderWindow & window, Wave &wave, const int wave_ind);
};