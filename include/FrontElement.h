#pragma once

#include"Vector2.h"

using namespace my_math;

class FrontElement : Element {
 public:
  FrontElement() = delete;

  explicit FrontElement(const Vector2 & position);

  override bool Draw() const = 0;

  override bool Dump() const = 0;

  bool SetPhase(const float phase);

  bool SetAmplitude(const float amplitude);

  virtual ~FrontElement();

 private:
  float amplitude_;
}
