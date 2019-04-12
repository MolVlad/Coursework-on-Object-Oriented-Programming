#pragma once

#include"Vector2.h"

using namespace my_math;

class Source : Element {
 public:
  Source();

  explicit Source(const Vector2 & position);

  virtual bool Draw() const = 0;

  virtual bool Dump() const = 0;

  virtual float GetFieldStrength() const = 0;

  virtual bool SetFieldStrength(const float field_strength);

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

  float GetFieldStrength() const override;

  bool SetFieldStrength(const float field_strength) override;

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

  float GetFieldStrength() const override;

  bool SetFieldStrength(const float field_strength) override;

 private:
  float field_strength_;
};
