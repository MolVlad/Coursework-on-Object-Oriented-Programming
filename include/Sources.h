#pragma once

#include"Vector2.h"

using namespace my_math;

class Source : Element {
 public:
  Source() = delete;

  explicit Source(const Vector2 & position);

  virtual bool Draw() const = 0;

  virtual bool Dump() const = 0;

  bool SetPhase(const float phase);

  bool SetAmplitude(const float amplitude);

  virtual ~Source();

 private:
  float phase_;
  float amplitude_;
};


class Dipole : Source {
 public:
  Dipole() = delete;

  explicit Dipole(const Vector2 & position);

  bool Draw() const;

  bool Dump() const;

  bool SetImageScale(const float image_scale);

  bool SetImageDirection();

  float GetFieldStrength() const;

  ~Dipole();
};


class FrontElement : Element {
 public:
  explicit FrontElement(const Vector2 & position);

  bool Draw() const;

  bool Dump() const;

  float GetFieldStrength() const;

  bool SetFieldStrength(const float field_strength);

 private:
  float field_strength_;
};
