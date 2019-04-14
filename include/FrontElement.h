#pragma once

#include"Vector2.h"
#include"Element.h"

using namespace my_math;

class FrontElement : public Element {
 public:
  FrontElement();

  explicit FrontElement(const Vector2 & position);

  bool Draw() const override;

  bool Dump() const override;

  float GetAmplitude() const;

  bool SetAmplitude(const float amplitude);

  virtual ~FrontElement();

 private:
  float amplitude_;
};
