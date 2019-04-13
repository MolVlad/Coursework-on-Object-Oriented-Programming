#include "vector2.h"
#include <iostream>

namespace Modulation {

KernelVector2::KernelVector2(void)
    :  x_(0),
       y_(0) {
  }

KernelVector2::KernelVector2(VECTOR_TYPE  x, VECTOR_TYPE  y)
    :  x_(x),
       y_(y)  {
}

KernelVector2::KernelVector2(const KernelVector2 & vect)
    :  x_(vect.x_),
       y_(vect.y_) {
}   

KernelVector2 & KernelVector2::operator=(const KernelVector2 & vect) {
  x_ = vect.x_;
  y_ = vect.y_;
  return *this;
}

KernelVector2 & KernelVector2::operator=(const KernelVector2 && vect) {
  x_ = vect.x_;
  y_ = vect.y_;
  return *this;
}

KernelVector2 & KernelVector2::operator+=(const KernelVector2 & vect) {
  x_ += vect.x_;
  y_ += vect.y_;	
  return *this;
}

KernelVector2 & KernelVector2::operator*=(const VECTOR_TYPE  k) {
  x_ *= k;
  y_ *= k;	
  return *this;
}

};
