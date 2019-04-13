#pragma once
#include <iostream>

namespace Modulation {

typedef float VECTOR_TYPE;

class KernelVector2 {
 public:
  // Base functions.
  KernelVector2(void);
  KernelVector2(VECTOR_TYPE  x, VECTOR_TYPE  y);
  ~KernelVector2(void) {
  }

  KernelVector2(const KernelVector2 & vect);
  KernelVector2 & operator=(const KernelVector2 & vect);
  KernelVector2 & operator=(const KernelVector2 && vect);
  
  // Interface functions.

  // Just adding vectors.
  KernelVector2 & operator+=(const KernelVector2 & vect);

  // Just subtracting vectors. 
  KernelVector2 & operator-=(const KernelVector2 & vect);

  // Multiply by k.
  KernelVector2 operator*(const VECTOR_TYPE  k) const;

  // Additional functions.
  VECTOR_TYPE  Len(void) const;
  void Reset(VECTOR_TYPE  x, VECTOR_TYPE  y);
  void Rotate(VECTOR_TYPE  degree);
  void Print(void) const {
   std::cout << "x_ = " << x_ << " y_ = " << y_ << std::endl;    
  }

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

  void new_func(void) {
    std::cout << x_;
    std::cout << y_;
  }  


  // Just adding vectors.
  Vector2 operator+(const Vector2 & vect) const;

  // Just subtracting vectors. 
  Vector2 operator-(const Vector2 & vect) const;

  // Multiply by -1.
  Vector2 operator-(void) const;

  // Division by k.
  Vector2 operator/(const VECTOR_TYPE  k) const;

  // Scalar composition.
  VECTOR_TYPE  operator*(const Vector2 & vect) const;

  // Vector composition.
  VECTOR_TYPE  operator^(const Vector2 & vect) const;

  // Additional functions.
  VECTOR_TYPE  SquareLen(void) const;

  // Return rotated vector.
  Vector2 getRotated(VECTOR_TYPE  degree) const;

  // Length of vector is 1 now.
  Vector2 Norm(void);
};

// Addition to override operators.
Vector2 operator*(VECTOR_TYPE k, const Vector2 & vect);
};



