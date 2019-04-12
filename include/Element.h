#pragma once

#include"Vector2.h"

using namespace my_math;

class Element {
 public:
  Element() = delete;

  explicit Element(const Vector2 & position);

  virtual bool Draw() const = 0;

  virtual bool Dump() const = 0;

  Vector2 GetPosition() const;

  Vector2 GetDirection() const;

  bool SetPosition(const Vector2 & position);

  bool SetDirection(const Vector2 & direction);

  virtual ~Element();

 private:
  Vector2 position_;
  Vector2 direction_;
};
