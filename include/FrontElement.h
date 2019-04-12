#pragma once

#include"Vector2.h"
#include"Element.h"

using namespace my_math;

class FrontElement : public Element {
 public:
  FrontElement() = delete;

  explicit FrontElement(const Vector2 & position);

  bool Draw() const override;

  bool Dump() const override;

  bool SetPhase(const float phase);

  bool SetAmplitude(const float amplitude);

  virtual ~FrontElement();

 private:
  float amplitude_;
};
