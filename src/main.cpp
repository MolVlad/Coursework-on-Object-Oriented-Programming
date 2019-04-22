#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Store.h"
#include "Wave.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using namespace my_math;

int main()
{
  Dipole dipole(Vector2(1, 2));
  dipole.SetPhase(13);
  dipole.SetAmplitude(12);
  dipole.SetPosition(Vector2(14, 13.5));
  dipole.SetDirection(Vector2(1, 0));

  Wave wave;
  FrontElement front_element(Vector2(1, 2));
  front_element.SetAmplitude(14);
  front_element.SetDirection(Vector2(1, 0));

  wave.Push(front_element);
  wave.Push(front_element);
  wave.Push(front_element);
  wave.Push(front_element);

  Store store;

  store.Push(dipole);
  store.Push(dipole);
  store.Push(dipole);
  store.Push(dipole);

  store.Push(wave);
  store.Push(wave);
  store.Push(wave);
  store.Push(wave);

  store.Dump();

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