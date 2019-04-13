#pragma once

#include<iostream>

namespace my_math {

class Vector2
{
 public:
  Vector2(const Vector2 &v);

  Vector2(const float x = 0, const float y = 0);

  float GetLength() const;

  float GetSquareLength() const;

  Vector2 GetNormalized() const;

  Vector2 GetPerpendicular() const;

  Vector2 operator+(const Vector2& other) const;

  void operator+=(const Vector2& other);

  Vector2 operator-(const Vector2& other) const;

  void operator-=(const Vector2& other);

  Vector2 operator*(const float k) const;

  Vector2 operator/(const float k) const;

  ~Vector2();


 private:
  float x_, y_;
};

std::ostream& operator<<(std::ostream& stream, const Vector2& v);

std::istream& operator>>(std::istream& stream, Vector2& v);

Vector2 operator*(float k, const Vector2& v);

} /* namespace my_math */
