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
  time_from_start = 0.;
}

Store::~Store()
{

}


bool Store::CheckCollisions(const FrontElement & front_element) const
{

  VECTOR_TYPE front_element_x_position = front_element.GetPosition( ).GetX( );
  for (auto& diffraction_grating : diffraction_gratings_)
  {
    if (front_element_x_position <= diffraction_grating.Right( ) && 
        front_element_x_position >= diffraction_grating.Left( ) - DEFAULT_FRONT_ELEMENT_RADIUS)
    {
      return false;
    }
  }
  return true;
}


bool Store::DrawHalfWave(sf::RenderWindow & window, const Vector2 & main_front_element_position, const bool is_top_part,
                         const int wave_ind)
{
  Vector2 next_position = main_front_element_position;
  FrontElement next = FrontElement(next_position);
  float strength = 0.;
  static Vector2 reference_direction(0, 1);

  // It is to fixing wave looping.
  int element_number = 0;

  #ifdef STORE_DRAW_DEBUG
  std::cout << "Positive direction\n";
  #endif /* STORE_DRAW_DEBUG */

    // second condition to fixing wave looping
  while (next.IsOnScreen() && (element_number < MAX_ELEMENT_NUMBER))
  {
    Vector2 front_direction = GetFieldStrength(next.GetPosition());
    strength = front_direction.Len();
    front_direction.Norm();

    // it is to fixing wave looping
    if (((front_direction * reference_direction) > 0 && is_top_part)
        || (front_direction * reference_direction) < 0 && !is_top_part)
    {
      front_direction *= -1;
    }

    next_position += front_direction * FRONT_ELEMENT_STEP;


    #ifdef STORE_DRAW_DEBUG
    std::cout << "\t" << element_number << " front_direction: " << front_direction <<
                 " next_pos: " << next_position << " strength: " << strength << std::endl;
    #endif /* STORE_DRAW_DEBUG */

    next = FrontElement(next_position);

    // Handle collisions with diffraction gratings. 
    #ifdef USING_DIFFRACTION_GRATING
    if (!CheckCollisions(next))
    {
      DRAWN_SIDES old_drawn_side = waves_[wave_ind].GetDrawnSides();

      Wave new_wave;
      new_wave.Push(next);
      if (old_drawn_side == BOTH_SIDES)
      {
        PushWaveMainElement(next_position, front_direction, 1);
        PushWaveMainElement(next_position, front_direction, -1);
        std::swap(waves_[wave_ind], waves_[waves_.size() - 1]);
        waves_.pop_back();

        #ifdef COLLISION_DEBAG
        std::cout << "Double collision\n";
        #endif
        return false;
      }
      if (is_top_part)
      {
        new_wave.SetDrawnSides(TOP_SIDE);

        #ifdef COLLISION_DEBAG
        std::cout << "Top collision!!!\n";
        #endif
      }
      else
      {
        new_wave.SetDrawnSides(BOTTOM_SIDE);

        #ifdef COLLISION_DEBAG
        std::cout << "Bottom collision!!!\n";
        #endif
      }
      Push(new_wave);

      std::swap(waves_[wave_ind], waves_[waves_.size() - 1]);
      waves_.pop_back();
   
      return false;
    }
    #endif


    next.DrawColor(window, strength);

    #ifdef DRAW_STEP_BY_STEP
    sleep(1);
    window.display();
    #endif /* DRAW_STEP_BY_STEP */

   element_number++;
  }
  return true;
}

void Store::PushWaveMainElement(const Vector2 & position, Vector2 & direction, const signed char factor)
{
  static Vector2 reference_direction(0, 1);
  Wave part_wave;
  if ((direction * reference_direction * factor) > 0)
  {
    direction *= -1;
  }
  part_wave.Push(FrontElement(position + direction * FRONT_ELEMENT_STEP * COLLISIION_SCALE));
  if (factor == 1)
  {
    part_wave.SetDrawnSides(TOP_SIDE);
  }
  else
  {
    part_wave.SetDrawnSides(BOTTOM_SIDE);
  }
  Push(part_wave);
  return;
}

bool Store::HandleWave(sf::RenderWindow & window, Wave &wave, const int wave_ind)
{

    FrontElement & main_front_element = wave.GetMain();

    Vector2 main_front_element_position = main_front_element.GetPosition();
    Vector2 front_direction = GetFieldStrength(main_front_element_position);
    main_front_element.DrawColor(window, front_direction.Len( ));


    // Handle collisions with diffraction gratings. 
    #ifdef USING_DIFFRACTION_GRATING
    if (!CheckCollisions(wave.GetMain( )))
    {
      DRAWN_SIDES old_drawn_side = wave.GetDrawnSides();
      front_direction.Norm( );

      static Vector2 reference_direction(0, 1);

      if (old_drawn_side != TOP_SIDE)
      {
        PushWaveMainElement(main_front_element_position, front_direction, -1);
      }


      if (old_drawn_side != BOTTOM_SIDE)
      {
        PushWaveMainElement(main_front_element_position, front_direction, 1);
      } 

      std::swap(waves_[wave_ind], waves_[waves_.size() - 1]);
      waves_.pop_back();  

      #ifdef COLLISION_DEBAG
      std::cout << "Collision of main element!!!\n";
      #endif

      return false;
    }
    #endif // USING_DIFFRACTION_GRATINGS.


    #ifdef STORE_DRAW_DEBUG
    std::cout << "Main: " << main_front_element_position << " strength: " << strength << std::endl;
    #endif /* STORE_DRAW_DEBUG */


    #ifdef DRAW_ALL_FRONT_ELEMENTS

    if (wave.GetDrawnSides() != BOTTOM_SIDE)
    {
      // Draw top part.
      if (!DrawHalfWave(window, main_front_element_position, true, wave_ind))
      {
        return false;
      }
    }

    if (wave.GetDrawnSides() != TOP_SIDE)
    {
      // Draw bottom part.
      if (!DrawHalfWave(window, main_front_element_position, false, wave_ind))
      {
        return false;
      }
      #endif /* DRAW_ALL_FRONT_ELEMENTS */
    }

    return true;
}

bool Store::HandleAllWaves(sf::RenderWindow & window)
{
  for (int ind = 0; ind < waves_.size( ); ind++)
  {
    if (!HandleWave(window, waves_[ind], ind))
    {
      return false;
    } 
  }
  return true;
}


bool Store::Draw(sf::RenderWindow & window) {

  #ifdef DRAW_STORE_TIMER
  std::chrono::high_resolution_clock::time_point debag_time_stamp = std::chrono::high_resolution_clock::now();
  #endif

  dipole_area_.Draw(window);

  for (auto& diffraction_grating : diffraction_gratings_) 
  {
    diffraction_grating.Draw(window);
  }

  for(auto& dipole : dipoles_) {
    dipole.Draw(window);
  }

  if(dipoles_.size() == 0)
  {
    return false;
  }

  unsigned int dipoles_number = dipoles_.size();

  // Find description in documentation to this function.
  while (!HandleAllWaves(window)) {
  }


  // For 10 waves it is neccesary approximately 0.537001, for one wave 0.0534042.
  #ifdef DRAW_STORE_TIMER
  std::chrono::duration<float> debag_diff = std::chrono::high_resolution_clock::now() - debag_time_stamp;
  std::cout << debag_diff.count( ) << std::endl; 
  #endif

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

bool Store::Push(const DiffractionGrating & diffraction_grating)
{
  #ifdef STORE_DEBUG
  std::cout << "Store::Push(diffraction_grating)" << std::endl;
  #endif /* STORE_DEBUG */

  diffraction_gratings_.push_back(diffraction_grating);

  #ifdef STORE_DEBUG
  std::cout << "Store::Push(diffraction_grating) end" << std::endl;
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
  #ifdef GET_FIELD_STRENTH_TIMER
  std::chrono::high_resolution_clock::time_point debag_time_stamp = std::chrono::high_resolution_clock::now();
  #endif

  Vector2 result(0, 0);

  std::vector<std::future<Vector2> > f;
  for(auto& dipole : dipoles_)
  {
    f.push_back(std::async([&]() {
      return dipole.GetFieldStrength(position, time_from_start);
      })
    );
  }

  for(auto& i : f)
    result += i.get();

  // For 10 di;oles  it is neccesary approximately 0.000205641, for one dipole 2.8404e-05.
  #ifdef GET_FIELD_STRENTH_TIMER
  std::chrono::duration<float> debag_diff = std::chrono::high_resolution_clock::now() - debag_time_stamp;
  std::cout << debag_diff.count( ) << std::endl; 
  #endif

  return result;
}

bool Store::UpdateTime()
{
  static std::chrono::high_resolution_clock::time_point time_stamp = time_start;

  std::chrono::duration<float> diff = std::chrono::high_resolution_clock::now() - time_stamp;

  time_stamp = std::chrono::high_resolution_clock::now();

  t = diff.count() / TIME_SCALE;

  time_from_start += t;
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

  #ifdef MOVE_WAVES_TIMER
  std::chrono::high_resolution_clock::time_point debag_time_stamp = std::chrono::high_resolution_clock::now();
  #endif

  if (dipoles_.size() == 0)
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

  // It is neccesary nearly 7.4659e-05 for it without waves and for a great amount of waves:.0.0010453.
  #ifdef MOVE_WAVES_TIMER
  std::chrono::duration<float> debag_diff = std::chrono::high_resolution_clock::now() - debag_time_stamp;
  std::cout << debag_diff.count( ) << std::endl; 
  #endif
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

  position += (speed_direction / DISTANT_SCALE) * FRONT_ELEMENT_MOVE_SPEED * t;
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