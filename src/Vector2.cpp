#include "vector2.h"
#include <iostream>

namespace Modulation {

// Functions of KernelVector2.

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

//Functions of Vector2.

Vector2 Vector2::operator+(const Vector2 & vect) const {
    Vector2 new_vect = Vector2(vect); 
    new_vect += *this;
    return new_vect;
}

Vector2 & Vector2::operator-=(const Vector2 & vect) {
  *this += vect;
  *this *= -1;
  return *this;
}

Vector2 Vector2::operator-(const Vector2 & vect) const {
  Vector2 new_vect = Vector2(*this);
  new_vect += vect * (-1);
  return new_vect;
}

Vector2 Vector2::operator-(void) const {
  Vector2 new_vect = Vector2(*this);
  new_vect *= (-1);	
  return new_vect;
}

Vector2 Vector2::operator*(const VECTOR_TYPE  k) const {
  Vector2 new_vect = Vector2(*this);
  new_vect *= k;	
  return new_vect;
}

Vector2 Vector2::operator/(const VECTOR_TYPE  k) const {
  Vector2 new_vect = Vector2(*this);
  new_vect *= 1 / k;	
  return new_vect;
}

VECTOR_TYPE  Vector2::SquareLen(void) const {
	float len = Len( );
    return len * len;
}

Vector2 Vector2::GetRotated(const VECTOR_TYPE  degree) const {
  Vector2 new_vect = Vector2(*this);
  new_vect.Rotate(degree);
  return new_vect;
}

void Vector2::Norm(void) {
  *this *= 1 / Len( );
  return ;	
}

Vector2 operator*(const VECTOR_TYPE k, const Vector2 & vect)
{
	Vector2 new_vect = Vector2(vect);
	new_vect *= k;
	return new_vect;
}

};
