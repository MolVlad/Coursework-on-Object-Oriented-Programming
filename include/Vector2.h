#pragma once
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

namespace my_math {

const float PI = 3.141593;
const float ONE_RADIAN = PI / 180;
const float ZERO_VECTOR = -1;
typedef float VECTOR_TYPE;

class KernelVector2 {
 public:
  // Base functions.
  KernelVector2(void);
  KernelVector2(VECTOR_TYPE  x, VECTOR_TYPE  y);
  virtual ~KernelVector2(void) {
  }

  KernelVector2(const KernelVector2 & vect);
  KernelVector2(const sf::Vector2i & vect);
  KernelVector2(const sf::Vector2f & vect);

  KernelVector2 & operator=(const KernelVector2 & vect);
  KernelVector2 & operator=(const KernelVector2 && vect);
  void Dump(void) const;
  // Interface functions.

  // Just adding vectors.
  KernelVector2 & operator+=(const KernelVector2 & vect);

  // Multiply by k.
  KernelVector2 & operator*=(const VECTOR_TYPE  k);

  // Additional functions.
  VECTOR_TYPE  Len(void) const;
  void Reset(const VECTOR_TYPE  x, const VECTOR_TYPE  y);
  void Rotate(const VECTOR_TYPE  degree);
  float GetX(void) const;
  float GetY(void) const;
 protected:
  VECTOR_TYPE  x_;
  VECTOR_TYPE  y_;
};


// Shell class
class Vector2 : public KernelVector2 {
 public:
  // Base functions.
  Vector2(void) 
      : KernelVector2( ) {
  }

  Vector2(VECTOR_TYPE  x, VECTOR_TYPE  y)
      :  KernelVector2(x, y) {
  }

  ~Vector2(void) {
  }

  Vector2(const Vector2 & vect) 
      :  KernelVector2(vect) {
  }

  Vector2(const sf::Vector2i & vect)
      : KernelVector2(vect) {
  }

  Vector2(const sf::Vector2f & vect)
      : KernelVector2(vect) {
  }

  Vector2 & operator=(const Vector2 & vect);

  // Just adding vectors.
  Vector2 operator+(const Vector2 & vect) const;

  // Just subtracting vectors. 
  Vector2 & operator-=(const Vector2 & vect);
  Vector2 operator-(const Vector2 & vect) const;

  // Multiply by -1.
  Vector2 operator-(void) const;

  // Multiply by k.
  Vector2 operator*(const VECTOR_TYPE  k) const;

  // Division by k. Situation 0 / 0 and (const != 0) / 0 is correct, but poison vector.
  Vector2 operator/(const VECTOR_TYPE  k) const;

  // Additional functions.
  VECTOR_TYPE  SquareLen(void) const;

  // Return rotated vector.
  Vector2 GetRotated(const VECTOR_TYPE degree) const;

  // Get Rotation from hour zero (clockwise rotation).
  float GetClockwiseRotation(int* code_error) const;

  // Length of vector is 1 now.
  void Norm(void);

  // Scalar muliplication
  float operator*(const Vector2& other) const;

  float GetCosAngleBetweenVectors(const Vector2 & b) const;

  friend std::ostream& operator<<(std::ostream& stream, const Vector2& v);

  friend std::istream& operator>>(std::istream& stream, Vector2& v);
};

// Addition to override operators.
Vector2 operator*(const VECTOR_TYPE k, const Vector2 & vect);

};  // namespace my_math
