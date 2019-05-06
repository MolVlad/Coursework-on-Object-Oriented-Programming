#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "Element.h"
#include "DiffractionGrating.h"

//#define FRONT_ELEMENT_DEBUG 1

namespace my_math
{
class FrontElement : public Element {
 public:
  FrontElement();

  explicit FrontElement(const Vector2 & position);

  FrontElement(const FrontElement &that);

  FrontElement(FrontElement &&that);

  void Swap(FrontElement & that);

  FrontElement& operator=(const FrontElement &that);

  FrontElement& operator=(FrontElement &&that);   

  bool Draw(sf::RenderWindow & window) override;

  bool DrawColor(sf::RenderWindow & window, float strength);

  bool Dump() const override;

  float GetAmplitude() const;

  bool SetAmplitude(const float amplitude);

  bool IsFarFromCenter(const WAVE_STATUSES wave_status, const DRAWN_SIDES drawn_sides) const;

  bool IsOnScreen(const DiffractionGrating *diffraction_grating) const;

  bool SetRGBA(int R, int G, int B, int A);

  virtual ~FrontElement();

 private:
  float amplitude_;
  sf::CircleShape circle_shape_;
};

} // End of namespace my_math.
