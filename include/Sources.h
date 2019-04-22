#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "Element.h"
#include <assert.h>

#define DIPOLE_DEBUG 1

using namespace my_math;

const float DIPOLE_SCALE_X = 0.1;
const float DIPOLE_SCALE_Y = 0.1;

const float TIME_SCALE = 10;
const float LIGHT_SPEED = 10000;
const float CYCLIC_FREQUENCY = 10;
const float DEFAULT_PHASE = 0;
const float DEFAULT_AMPLITUDE = 10000;

class Source : public Element {
 public:
  Source();

  Source(const Vector2 & position);

  virtual bool Draw(sf::RenderWindow & window) = 0;

  virtual bool Dump() const = 0;

  virtual float GetFieldStrength(const Vector2 & point) const = 0;

  bool SetPhase(const float phase);

  bool SetAmplitude(const float amplitude);

  virtual ~Source();

 protected:
  float phase_;
  float amplitude_;
};

const float X_SCALE = 50;
const float Y_SCALE = 50;

class Dipole : public Source {
 public:
  Dipole();

  explicit Dipole(const Vector2 & position);

  bool Draw(sf::RenderWindow & window) override;

  bool Dump() const override;

  // get field strength from this source in point
  float GetFieldStrength(const Vector2 & point) const override;

  // Image_scale is increase in size. It should be positive.
  bool SetImageScale(const float image_scale);

  bool SetImageDirection(const float direction);

  ~Dipole();
};

class SecondarySource : public Source {
 public:
  SecondarySource();

  explicit SecondarySource(const Vector2 & position);

  bool Draw(sf::RenderWindow & window) override;

  bool Dump() const override;

  // get field strength from this source in point
  float GetFieldStrength(const Vector2 & point) const override;

  ~SecondarySource();

 private:
  float field_strength_;
};
