#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Store.h"
#include "Wave.h"
#include "Handlers.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using namespace my_math;

int main()
{
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Coursework");

  Store store;

  while(window.isOpen())
  {
    window.clear();
		handleEvent(window, store);

    // TO DO

    window.display();
  }

  return 0;
}
