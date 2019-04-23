#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>

#include "Store.h"
#include "Wave.h"
#include "Handlers.h"


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
    HandleEvent(window, store);
    HandleDraw(window, store);
    HandleStore(store);

    window.display();
  }

  return 0;
}
