#pragma once

#include<vector>

class Store {
 public:

  bool Push(const Dipole & dipole);

  bool Push(const FrontElement & front_element);

  bool Draw() const;

  bool Dump() const;

 private:
  std::vector<Dipole> dipoles_;
  std::vector<FrontElement> front_elements_;
};
