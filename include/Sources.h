#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "Element.h"

#define DIPOLE_DEBUG 1

using namespace my_math;

class Source : public Element {
 public:
  Source();

  Source(const Vector2 & position);

  virtual bool Draw(const sf::RenderWindow & window) const = 0;

  virtual bool Dump() const = 0;

  virtual float GetFieldStrength(const Vector2 point) const = 0;

  bool SetPhase(const float phase);

  bool SetAmplitude(const float amplitude);

  virtual ~Source();

 protected:
  float phase_;
  float amplitude_;

};


class Dipole : public Source {
 public:
  Dipole();

  explicit Dipole(const Vector2 & position);

  bool Draw(const sf::RenderWindow & window) const override;

  bool Dump() const override;

  // get field strength from this source in point
  float GetFieldStrength(const Vector2 point) const override;

  bool SetImageScale(const float image_scale);

  bool SetImageDirection();

  ~Dipole();
};

class SecondarySource : public Source {
 public:
  SecondarySource();

  explicit SecondarySource(const Vector2 & position);

  bool Draw(const sf::RenderWindow & window) const override;

  bool Dump() const override;

  // get field strength from this source in point
  float GetFieldStrength(const Vector2 point) const override;

  ~SecondarySource();

 private:
  float field_strength_;
};