#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Store.h"

#define MOUSE_DEBUG 1

bool handleEvent(sf::RenderWindow &window, Store &store);
bool handleMouse(sf::RenderWindow &window, sf::Event event, Store &store);
bool handleDraw(sf::RenderWindow &window, Store &store);