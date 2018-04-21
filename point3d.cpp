#include "point3d.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

std::string Point3D::ToString() const {
  std::ostringstream os;
  os << x_<< " " << y_ << " ";
  os << z_;
  return os.str();
}

double Point3D::DistanceTo(Point3D other) {
  double x_term = x_ - other.getX();
  double y_term = y_ - other.getY();
  double z_term = z_ - other.getZ();
  return std::sqrt((x_term * x_term) + (y_term * y_term) + (z_term * z_term));
}

Vec3D Point3D::VecTo(Point3D other) const {
  return {other.getX() - getX(),
    other.getY() - getY(),
    other.getZ() - getZ()
  };
}

Point3D Point3D::Add(Vec3D other) {
  return {getX() + other.X(),
    getY() + other.Y(),
    getZ() + other.Z()};
}

Point3D Point3D::Subtract(Point3D other) {
  return {getX() - other.getX(),
    getY() - other.getY(),
    getZ() - other.getZ()};
}