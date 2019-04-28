#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <assert.h>

#include "Store.h"

//#define MOUSE_DEBUG 1

namespace handler {

//#define DIPOLE_PHASE_DEBUG 1
//#define KEY_DEBUG 1
//#define MOUSE_DEBUG 1

// DIRECTION_0 is default value - up arrow. Сlockwise rotation.
enum PosssibleDipoleDirections {
  DIRECTION_0 = 180,
  DIRECTION_45 = 225,
  DIRECTION_90 = 270,
  DIRECTION_135 = 315,
  DIRECTION_180 = 0,
  DIRECTION_225 = 45,
  DIRECTION_270 = 90,
  DIRECTION_315 = 135
};


enum PosssibleDipolePhase {
  PHASE_0 = 0,
  PHASE_36 = 36,
  PHASE_72 = 72,
  PHASE_108 = 108,
  PHASE_144 = 144,
  PHASE_180 = 180,
  PHASE_216 = 216,
  PHASE_252 = 252,
  PHASE_288 = 288,
  PHASE_324 = 324
};

bool HandleEvent(sf::RenderWindow &window, Store &store);
int GetTextureIndex(const PosssibleDipolePhase phase);
bool HandleMouse(const sf::RenderWindow &window, const sf::Event &event, Store &store,
                 PosssibleDipoleDirections *dipole_direction, PosssibleDipolePhase *dipole_phase);
bool HandleKey(const sf::Event &event, Store & store, PosssibleDipoleDirections *dipole_direction,
               PosssibleDipolePhase *dipole_phase);
bool HandleDraw(sf::RenderWindow &window, Store &store);
bool HandleStore(Store &store);

// Don't set dipoles inside dipole area.
bool IsRightPosition(const sf::Vector2i & position);

} // End of namespace handler.
