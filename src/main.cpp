#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Store.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using namespace my_math;

int main()
{
  Dipole dipole(Vector2(1, 2));
  dipole.Dump();

/*
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Coursework");

  while(window.isOpen())
  {
    window.clear();

    // TO DO

    window.display();
  }
  */

  return 0;
}
