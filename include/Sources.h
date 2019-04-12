#pragma once

#include"Vector2.h"
#include"Element.h"

using namespace my_math;

class Source : Element {
 public:
  Source();

  virtual bool Draw() const = 0;

  virtual bool Dump() const = 0;

  virtual float GetFieldStrength(const Vector2 point) const = 0;

  bool SetPhase(const float phase);

  bool SetAmplitude(const float amplitude);

  virtual ~Source();

 private:
  float phase_;
  float amplitude_;
};


class Dipole : Source {
 public:
  Dipole();

  explicit Dipole(const Vector2 & position);

  bool Draw() const override;

  bool Dump() const override;

  // get field strength from this source in point
  float GetFieldStrength(const Vector2 point) const override;

  bool SetImageScale(const float image_scale);

  bool SetImageDirection();

  ~Dipole();
};

class SecondarySource : Source {
 public:
  SecondarySource();

  explicit SecondarySource(const Vector2 & position);

  bool Draw() const override;

  bool Dump() const override;

  // get field strength from this source in point
  float GetFieldStrength(const Vector2 point) const override;

  ~SecondarySource();

 private:
  float field_strength_;
};
