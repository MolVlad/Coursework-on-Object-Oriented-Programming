#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Coursework");

  while(window.isOpen())
  {
    window.clear();

    // TO DO

    window.display();
  }

  return 0;
}
