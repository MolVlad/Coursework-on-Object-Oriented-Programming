#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>

#include "Store.h"
#include "Wave.h"
#include "Handlers.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using namespace my_math;

std::chrono::high_resolution_clock::time_point time_start;

int main()
{
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Coursework");

  time_start = std::chrono::high_resolution_clock::now();

  Store store;

  while(window.isOpen())
  {
    window.clear(sf::Color::White);
    handleEvent(window, store);
    handleDraw(window, store);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
      store.MoveWaves();

    // TO DO
    window.display();
  }

  return 0;
}
