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

  unsigned int dipoles_number = dipoles_.size();

  // it is to fixing wave looping
  int element_number = 0;

  for(auto& wave : waves_) {
    FrontElement & main_front_element = wave.GetMain();

    Vector2 main_front_element_position = main_front_element.GetPosition();
    float strength = GetFieldStrength(main_front_element_position).Len();
    main_front_element.DrawColor(window, strength);

    #ifdef STORE_DRAW_DEBUG
    std::cout << "Main: " << main_front_element_position << " strength: " << strength << std::endl;
    #endif /* STORE_DRAW_DEBUG */

    static Vector2 reference_direction(0, 1);

    #ifdef DRAW_ALL_FRONT_ELEMENTS

    Vector2 next_position;
    FrontElement next;

    //Positive direction
    next_position = main_front_element_position;
    next = FrontElement(next_position);

    element_number = 0;

    #ifdef STORE_DRAW_DEBUG
    std::cout << "Positive direction\n";
    #endif /* STORE_DRAW_DEBUG */

    // second condition to fixing wave looping
    while(next.IsOnScreen() && (element_number < MAX_ELEMENT_NUMBER))
    {
      Vector2 front_direction = GetFieldStrength(next.GetPosition());
      strength = front_direction.Len();
      front_direction.Norm();

      // it is to fixing wave looping
      if((front_direction * reference_direction) < 0)
        front_direction *= -1;

      next_position += front_direction * FRONT_ELEMENT_STEP;

      #ifdef STORE_DRAW_DEBUG
      std::cout << "\t" << element_number << " front_direction: " << front_direction << " next_pos: " << next_position << " strength: " << strength << std::endl;
      #endif /* STORE_DRAW_DEBUG */

      next = FrontElement(next_position);
      next.DrawColor(window, strength);


      #ifdef DRAW_STEP_BY_STEP
      sleep(0.2);
      window.display();
      #endif /* DRAW_STEP_BY_STEP */

      element_number++;
    }

    //Negative direction
    next_position = main_front_element_position;
    next = FrontElement(next_position);

    element_number = 0;

    #ifdef STORE_DRAW_DEBUG
    std::cout << "Negative direction\n";
    #endif /* STORE_DRAW_DEBUG */

    // second condition to fixing wave looping
    while(next.IsOnScreen() && (element_number < MAX_ELEMENT_NUMBER))
    {
      Vector2 front_direction = GetFieldStrength(next.GetPosition());
      strength = front_direction.Len();
      front_direction.Norm();

      // it is to fixing wave looping
      if((front_direction * reference_direction) > 0)
        front_direction *= -1;

      next_position += front_direction * FRONT_ELEMENT_STEP;

      #ifdef STORE_DRAW_DEBUG
      std::cout << "\t" << element_number << " front_direction: " << front_direction 
                << " next_pos: " << next_position << " strength: " << strength << std::endl;
      #endif /* STORE_DRAW_DEBUG */

      next = FrontElement(next_position);
      next.DrawColor(window, strength);

      #ifdef DRAW_STEP_BY_STEP
      sleep(1);
      window.display();
      #endif /* DRAW_STEP_BY_STEP */

      element_number++;
    }

    #endif /* DRAW_ALL_FRONT_ELEMENTS */
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


bool Store::RemoveDistantWaves()
{
  for (int i = 0; i < waves_.size(); i++)
  {
    if (waves_[i].GetMain().IsFarFromCenter())
    {
      std::swap(waves_[i], waves_[waves_.size() - 1]);
      waves_.pop_back();
    }
  }
  return true;
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


  std::vector<std::future<bool> > f;
  for (auto& wave : waves_)
  {
    f.push_back(std::async([&]() {
      MoveWave(wave);
      return true;
      })
    );
  }

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

  if ((speed_direction * distance_to_center) < 0)
    speed_direction *= -1;

  #ifdef STORE_MOVE_DEBUG
  std::cout << "\tt: " << time_ << std::endl;
  std::cout << "\tresult speed_direction: " << speed_direction << std::endl;
  #endif /* STORE_MOVE_DEBUG */

  #ifdef STOP_WAVES
  time_ = 0;
  #endif /* STOP_WAVES */

  float old_time = time_;
  time_ += TIME_IN_STEP;
  position += speed_direction * FRONT_ELEMENT_MOVE_SPEED * TIME_IN_STEP;
  front_element.SetPosition(position);

  #ifdef STORE_MOVE_DEBUG
  std::cout << "new position: " << position << std::endl;
  std::cout << "Store::MoveWave() end\n";
  std::cout << std::endl;
  #endif /* STORE_MOVE_DEBUG */
}

bool Store::Clear()
{
  for(auto & wave : waves_)
    wave.Clear();
  waves_.clear();
  dipoles_.clear();

  return true;
}
