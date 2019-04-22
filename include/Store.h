#pragma once

#include<vector>
#include <SFML/Graphics.hpp>

#include"Wave.h"
#include"Sources.h"

#define STORE_DEBUG 1

class Store {
 public:
  Store();

  bool Push(const Dipole & dipole);

  bool Push(const Wave & wave);

  bool Draw(sf::RenderWindow & window);

  bool Dump() const;

  ~Store();

 private:
  std::vector<Dipole> dipoles_;
  std::vector<Wave> waves_;
};
