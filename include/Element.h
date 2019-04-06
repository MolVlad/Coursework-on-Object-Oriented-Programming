#pragma once

#include"Vector2.h"

using namespace my_math;

class Element {
 public:
  explicit Element(const Vector2 & position, const Vector2 & direction);

  virtual bool Draw() const;

  virtual bool Dump() const;

  Vector2 GetPosition() const;

  Vector2 GetDirection() const;

  Vector2 SetPosition(const Vector2 & position) const;

  Vector2 SetDirection(const Vector2 & direction) const;

  virtual ~Element();

 private:
  Vector2 position_;
  Vector2 direction_;
};
