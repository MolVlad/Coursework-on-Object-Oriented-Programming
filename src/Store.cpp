#include "Store.h"

Store::Store()
{

}

Store::~Store()
{

}


bool Store::Draw(sf::RenderWindow & window)
{
  for (int ind = 0; ind < dipoles_.size( ); ind++) {
    dipoles_[ind].Draw(window);
  }

  for (int ind = 0; ind < waves_.size( ); ind++) {
    waves_[ind].Draw(window);
  }

  return true;
}

bool Store::Push(const Dipole & dipole)
{
  #ifdef STORE_DEBUG
  std::cout << "Store::Push(dipole)" << std::endl;
  #endif /* STORE_DEBUG */

  dipoles_.push_back(dipole);

  #ifdef STORE_DEBUG
  std::cout << "Store::Push(dipole) end" << std::endl;
  #endif /* STORE_DEBUG */

  std::cout << std::endl;
  return true;
}

bool Store::Push(const Wave & wave)
{
  #ifdef STORE_DEBUG
  std::cout << "Store::Push(wave)" << std::endl;
  #endif /* STORE_DEBUG */

  waves_.push_back(wave);

  #ifdef STORE_DEBUG
  std::cout << "Store::Push(wave) end" << std::endl;
  #endif /* STORE_DEBUG */

  std::cout << std::endl;
  return true;
}

bool Store::Dump() const
{
  #ifdef STORE_DEBUG
  std::cout << "Store::Dump()" << std::endl;
  #endif /* STORE_DEBUG */

  std::cout << "Print dipole_: " << dipoles_.size() << std::endl;
  for(auto& i : dipoles_)
  {
    i.Dump();
  }

  std::cout << "Print waves_: " << waves_.size() << std::endl;
  for(auto& i : waves_)
    i.Dump();

  #ifdef STORE_DEBUG
  std::cout << "Store::Dump() end" << std::endl;
  #endif /* STORE_DEBUG */

  std::cout << std::endl;
  return true;
}

Vector2 Store::GetFieldStrength(const my_math::Vector2 & position) const
{
  Vector2 result(0, 0);

  for(auto& i : dipoles_)
    result += i.GetFieldStrength(position);

  return result;
}
