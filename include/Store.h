#pragma once

#include<vector>

#include"FrontElement.h"
#include"Sources.h"

class Store {
 public:
  Store();

  bool Push(const Dipole & dipole);

  bool Push(const FrontElement & front_element);

  bool Draw() const;

  bool Dump() const;

  ~Store();

 private:
  std::vector<Dipole> dipoles_;
  std::vector<FrontElement> front_elements_;
};
