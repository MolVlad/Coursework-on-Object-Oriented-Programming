#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>
#include <ctime>

#include "Vector2.h"

using namespace my_math;

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const float DEFAULT_AREA_RADIUS = 30.;
const float DEFAULT_AREA_PCOUNT = 40.;
const float DEFAULT_AREA_CENTER_X = 0.;
const float DEFAULT_AREA_CENTER_Y = 300.;
const float MAX_DISTANCE_FROM_AREA_CENTER = 1000.;

const float DEFAULT_FRONT_ELEMENT_RADIUS = 2.;
const float DEFAULT_FRONT_ELEMENT_PCOUNT = 40.;
const float FRONT_ELEMENT_MOVE_SPEED = 3 * 100000000;
const float FRONT_ELEMENT_STEP = 0.5;
const int MAX_ELEMENT_NUMBER = 20000;
const float DISTANT_SCALE = 0.1;

const float DEFAULT_DIPOLE_DIRECTION = 180;
const float DIPOLE_SCALE_X = 0.015;
const float DIPOLE_SCALE_Y = 0.015;

const float DEFAULT_PHASE = 0;
const float DEFAULT_AMPLITUDE = 2000;
const float FREQUENCY = 50000000;
const float CYCLIC_FREQUENCY = 2 * PI * FREQUENCY;  // 50GHz
const float LIGHT_SPEED = 3 * 100000000;
const float WAVE_LENGTH =  LIGHT_SPEED / FREQUENCY;
const float WAVE_NUMBER = CYCLIC_FREQUENCY / LIGHT_SPEED;
const float TIME_SCALE = 100000000;

const int NUMBER_DIPOLE_TEXTURES = 10;
const char* const IMAGE_ARRAY[NUMBER_DIPOLE_TEXTURES] = {
  "images/dipole.png",
  "images/dipole36.png",
  "images/dipole72.png",
  "images/dipole108.png",
  "images/dipole144.png",
  "images/dipole180.png",
  "images/dipole216.png",
  "images/dipole252.png",
  "images/dipole288.png",
  "images/dipole324.png",
};

// Grating constants.
const char* const GRATING_TEXTURE = "images/black_grating_part.png";
const float GRATING_SCALE_X = 0.005;
const float GRATING_SCALE_Y = 0.5;
const float DEFAULT_GRATING_DIRECTION = 180.;
const float DEFAULT_GRATING_PEROID = SCREEN_HEIGHT;
const float DEFAULT_GRATING_SLOT_WIDTH = SCREEN_HEIGHT / 2;
const float COLLISIION_SCALE = 10.;
const Vector2 DEFAULT_SECONDARY_WAVE_DISPLACEMENT = Vector2(2., 0.);
const int NUMBER_SIDES = 4;

// If time to handle all actions is really big front element can flee diffraction grating.
const float FIXING_MISSING_LENGTH = 15.;

/// Modes of drawing waves.
enum DRAWN_SIDES
{ 
  TOP_SIDE = 0, ///< Draw only top part of the wave.
  BOTTOM_SIDE = 1, ///< Draw only bottom side of the wave. 
  BOTH_SIDES = 2 ///< Draw both parts of the wave.
};

/// Modes of finding strength for wave.
enum WAVE_STATUSES
{
  ORDINARY_WAVE = 0, ///< Wave from dipoles.
  SECONDARY_WAVE = 1 ///< Wave from secondary sources.
};


class Element {
 public:
  Element();

  explicit Element(const Vector2 & position);

  Element(const Element & that);

  Element(Element && that);

  virtual bool Draw(sf::RenderWindow & window) = 0;

  virtual bool Dump() const = 0;

  Vector2 GetPosition() const;

  float GetDirection() const;

  virtual bool SetPosition(const Vector2 & position);

  virtual bool SetDirection(const float direction);

  virtual ~Element();

 protected:
  Vector2 position_;
  float direction_;
};
