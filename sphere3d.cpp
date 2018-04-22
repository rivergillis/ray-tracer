#include "sphere3d.h"
#include <sstream>
#include <cmath>
#include <iostream>


std::string Sphere3D::ToString() const {
  std::ostringstream os;
  os << "Sphere3D @(" << center_.ToString() << ") radius " << radius_;
  return os.str();
}

bool Sphere3D::GetIntersection(Ray3D ray, Point3D& point, Vec3D& normal) const {
  // std::cout << "x: " << this->ToString() << " " << ray.ToString() << std::endl;
  double discriminant = pow(ray.Dir().Dot(center_.VecTo(ray.Origin())), 2) - 
    pow(center_.VecTo(ray.Origin()).Magnitude(), 2) +
    radius_ * radius_;

  if (discriminant < 0) {
    return false;
  }

  double neg_b = -(ray.Dir().Dot(center_.VecTo(ray.Origin())));

  if (discriminant == 0) {
    // intersection is behind us, don't bother calculating normal or point
    if (neg_b < 0) {
      return false;
    }
    // Calculate and set intersection point
    Point3D touch = ray.GetSample(neg_b);
    point.setX(touch.getX());
    point.setY(touch.getY());
    point.setZ(touch.getZ());

    // calculate and set normal
    Vec3D touch_normal = center_.VecTo(touch).Normalized();
    normal.Set(touch_normal);
    return true;
  } else {
    double first = neg_b + sqrt(discriminant);
    double second = neg_b - sqrt(discriminant);
    Point3D touch(0, 0, 0);

    if (first < 0 && second < 0) {
      // both intersections behind ray
      return false;
    } else if (first < 0) {
      touch = ray.GetSample(second);
    } else if (second < 0) {
      touch = ray.GetSample(first);
    } else if (first < second) {
      touch = ray.GetSample(first);
    } else {
      touch = ray.GetSample(second);
    }

    point.setX(touch.getX());
    point.setY(touch.getY());
    point.setZ(touch.getZ());

    // calculate and set normal
    Vec3D touch_normal = center_.VecTo(touch).Normalized();
    normal.Set(touch_normal);
    return true;
  }
}
