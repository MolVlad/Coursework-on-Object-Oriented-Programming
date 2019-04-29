#include "Store.h"

#include <chrono>
#include <utility>
#include <future>
#include <numeric>
#include <functional>
#include <unistd.h>

extern std::chrono::high_resolution_clock::time_point time_start;

Store::Store()
{

}

Store::~Store()
{

}

bool Store::Draw(sf::RenderWindow & window) {
  dipole_area_.Draw(window);

  for(auto& dipole : dipoles_) {
    dipole.Draw(window);
  }

  if(dipoles_.size() == 0)
  {
    return false;
  }

  for(int n = 0; n < SCREEN_WIDTH; n++)
    for(int k = 0; k < SCREEN_HEIGHT; k++) {
      std::cout << "(n,k) = ( " << n << "," << k << ")\n";
      Vector2 front_element_position(n, k);
      FrontElement front_element(Vector2(n, k));
      if(front_element.IsOnScreen())
      {
        float strength = GetFieldStrength(front_element_position).Len();
        front_element.DrawColor(window, strength);
      }
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
  std::cout << std::endl;
  #endif /* STORE_DEBUG */

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
  std::cout << std::endl;
  #endif /* STORE_DEBUG */

  return true;
}

bool Store::Dump() const
{
  #ifdef STORE_DEBUG
  std::cout << "Store::Dump()" << std::endl;
  #endif /* STORE_DEBUG */

  std::cout << "Print dipole_: " << dipoles_.size() << std::endl;
  for(auto& dipole : dipoles_)
  {
    dipole.Dump();
  }

  std::cout << "Print waves_: " << waves_.size() << std::endl;
  for(auto& wave : waves_)
    wave.Dump();

  #ifdef STORE_DEBUG
  std::cout << "Store::Dump() end" << std::endl;
  #endif /* STORE_DEBUG */

  std::cout << std::endl;
  return true;
}

Vector2 Store::GetFieldStrength(const my_math::Vector2 & position) const
{
  Vector2 result(0, 0);

  std::vector<std::future<Vector2> > f;
  for(auto& dipole : dipoles_)
  {
    f.push_back(std::async([&]() {
      return dipole.GetFieldStrength(position);
      })
    );
  }

  for(auto& i : f)
    result += i.get();

  return result;
}

bool Store::UpdateTime()
{
  static std::chrono::high_resolution_clock::time_point time_stamp = time_start;

  std::chrono::duration<float> diff = std::chrono::high_resolution_clock::now() - time_stamp;

  time_stamp = std::chrono::high_resolution_clock::now();

  t = diff.count() / TIME_SCALE;
}

float Store::GetTime()
{
  return t;
}

bool Store::RemoveDistantWaves()
{
  for (int i = 0; i < waves_.size(); i++)
  {
    if(waves_[i].GetMain().IsFarFromCenter())
    {
      std::swap(waves_[i], waves_[waves_.size() - 1]);
      waves_.pop_back();
    }
  }
}

bool Store::MoveWaves()
{
  #ifdef STORE_DEBUG
  std::cout << "Store::MoveWaves()" << std::endl;
  #endif /* STORE_DEBUG */

  if(dipoles_.size() == 0)
  {
    return false;
  }

  float t = GetTime();

  std::vector<std::future<bool> > f;
  for (auto& i : waves_)
  {
    f.push_back(std::async([&]() {
      MoveWave(i);
      return true;
      })
    );
  }

  for(auto& result : f) 
    result.get();

  #ifdef STORE_DEBUG
  std::cout << "Store::MoveWaves() end" << std::endl;
  std::cout << std::endl;
  #endif /* STORE_DEBUG */

  return true;
}


bool Store::MoveWave(Wave & wave)
{
  FrontElement & front_element = wave.GetMain();
  Vector2 position = front_element.GetPosition();

  Vector2 field_strength = GetFieldStrength(front_element.GetPosition());
  Vector2 speed_direction = field_strength.GetRotated(-90);
  speed_direction.Norm();

  Vector2 distance_to_center = position - Vector2(DEFAULT_AREA_CENTER_X, DEFAULT_AREA_CENTER_Y);

  #ifdef STORE_MOVE_DEBUG
  std::cout << "Store::MoveWave()\n";
  std::cout << "\tposition: " << position << std::endl;
  std::cout << "\tfield_strength: " << field_strength << std::endl;
  std::cout << "\tdistance_to_center " << distance_to_center << std::endl;
  std::cout << "\tspeed_direction: " << speed_direction << std::endl;
  std::cout << "\tscalar mult " << speed_direction * distance_to_center << std::endl;
  #endif /* STORE_MOVE_DEBUG */

  if((speed_direction * distance_to_center) < 0)
    speed_direction *= -1;

  #ifdef STORE_MOVE_DEBUG
  std::cout << "\tt: " << t << std::endl;
  std::cout << "\tresult speed_direction: " << speed_direction << std::endl;
  #endif /* STORE_MOVE_DEBUG */

  #ifdef STOP_WAVES
  t = 0;
  #endif /* STOP_WAVES */

  position += speed_direction / DISTANT_SCALE * FRONT_ELEMENT_MOVE_SPEED * t;
  front_element.SetPosition(position);

  #ifdef STORE_MOVE_DEBUG
  std::cout << "new position: " << position << std::endl;
  std::cout << "Store::MoveWave() end\n";
  std::cout << std::endl;
  #endif /* STORE_MOVE_DEBUG */
}

bool Store::Clear()
{
  for(auto & i : waves_)
    i.Clear();

  waves_.clear();

  dipoles_.clear();
}
