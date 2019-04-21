#pragma once

#include<vector>

#include"Wave.h"
#include"Sources.h"

class Store {
 public:
  Store();

  bool Push(const Dipole & dipole);

  bool Push(const Wave & wave);

  bool Draw() const;

  bool Dump() const;

  ~Store();

 private:
  std::vector<Dipole> dipoles_;
  std::vector<Wave> waves_;
};
