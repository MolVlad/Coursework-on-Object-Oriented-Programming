#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "FrontElement.h"
#include "DiffractionGrating.h"

//#define WAVE_DEBUG 1
//#define CREATING_SECONDARY_WAVE_DEBAG 1

namespace my_math
{

class Wave {
 public:
  Wave();

  Wave(const Wave &that);

  Wave(Wave &&that);  

  void Swap(Wave & that);

  Wave& operator=(const Wave & that);

  Wave& operator=(Wave && that);

  bool Draw(sf::RenderWindow & window);

  bool Dump() const;

  bool Push(const FrontElement & front_element);

  FrontElement & GetMain();

  bool Clear();

  void SetDrawnSides(const DRAWN_SIDES drawn_sides);

  DRAWN_SIDES GetDrawnSides(void) const;

  void SetWaveStatus(const WAVE_STATUSES wave_status);

  const WAVE_STATUSES GetWaveStatus(void) const;

  void SetDiffractionGrating(DiffractionGrating *diffraction_grating);

  DiffractionGrating* GetDiffractionGrating(void) const;

  void SetSecondarySourceNumber(const int source_number);

  int GetSecondarySourceNumber(void) const;   

  virtual ~Wave();

 protected:
  std::vector<FrontElement> front_elements_;
  DRAWN_SIDES drawn_sides_;
  WAVE_STATUSES wave_status_;
  DiffractionGrating *diffraction_grating_;

  // NUmber of dipole in diffraction_grating;
  int secondary_source_number_;

};

} //End of namespace my_math.