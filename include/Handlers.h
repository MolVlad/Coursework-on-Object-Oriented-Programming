#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Store.h"

#define MOUSE_DEBUG 1

bool HandleEvent(sf::RenderWindow &window, Store &store);
bool HandleMouse(sf::RenderWindow &window, sf::Event event, Store &store);
bool HandleDraw(sf::RenderWindow &window, Store &store);
bool HandleStore(Store &store);

// Don't set dipoles inside dipole area.
bool IsRightPosition(const sf::Vector2i & position);
