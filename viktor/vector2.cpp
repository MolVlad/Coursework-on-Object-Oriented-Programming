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

void KernelVector2::Dump(void) const
{
    std::cout << "x_ = " << x_ << " y_ = " << y_ << std::endl;
    return;
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

VECTOR_TYPE  KernelVector2::Len(void) const {
  return sqrt(x_ * x_ + y_ * y_);
}

void KernelVector2::Reset(const VECTOR_TYPE  x, const VECTOR_TYPE  y) {
  x_ = x;
  y_ = y;
  return;
}

void KernelVector2::Rotate(const VECTOR_TYPE degree) {
  if (!x_ && !y_) {
  	return;
  }

  VECTOR_TYPE angle = atan2(y_, x_);
  angle += (degree * PI) / 180;
  VECTOR_TYPE len = Len( );
  x_ = len * cos(angle);
  y_ = len * sin(angle);
  return;	
}

};
