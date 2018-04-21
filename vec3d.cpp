#include "vec3d.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

void Vec3D::Set(const Vec3D& other) {
  x_ = other.X();
  y_ = other.Y();
  z_ = other.Z();
}

double Vec3D::Dot(const Vec3D& other) const {
  return (X() * other.X()) + (Y() * other.Y()) + (Z() * other.Z());
}

Vec3D Vec3D::Divide(double amount) const {
  return {X() / amount, Y() / amount, Z() / amount};
}

Vec3D Vec3D::Multiply(double amount) const {
  return {X() * amount, Y() * amount, Z() * amount};
}

Vec3D Vec3D::Add(const Vec3D& other) const {
  return {X() + other.X(), Y() + other.Y(), Z() + other.Z()};
}

Vec3D Vec3D::Subtract(const Vec3D& other) const {
  return {X() - other.X(), Y() - other.Y(), Z() - other.Z()};
}

double Vec3D::Magnitude() const {
  return sqrt((X() * X()) + (Y() * Y()) + (Z() * Z()));
}

Vec3D Vec3D::Normalized() const {
  return Divide(Magnitude());
}

std::string Vec3D::ToString() const {
  std::ostringstream os;
  os << "Vec3D<" << X() << ", " << Y() << ", ";
  os << Z() << ">";
  return os.str();
}