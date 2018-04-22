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
  Vec3D OriginToCenter = center_.VecTo(ray.Origin());
  double A = ray.Dir().Dot(ray.Dir());
  double B = 2 * OriginToCenter.Dot(ray.Dir());
  double C = OriginToCenter.Dot(OriginToCenter) - radius_ * radius_;
  double discriminant = B * B - 4 * A * C;

  if (discriminant < 0) {
    return false;
  }
  // Calculate the two roots
  double root1 = (-B - sqrt(discriminant)) / 2 * A;
  double root2 = (-B + sqrt(discriminant)) / 2 * A;
  double solution = 0;

  // No positive roots
  if ((root1 < 0) && (root2 < 0)) {
    return false;
  } else if ((root1 < 0) && (root2 >= 0)) {
    solution = root2;
  } else if ((root2 < 0) && (root1 >= 0)) {
    solution = root1;
  } else if (root1 <= root2) {
    solution = root1;
  } else if (root2 <= root1) {
    solution = root2;
  }

  // set the intersection point
  point = ray.GetSample(solution);

  // set the normal
  normal.Set(center_.VecTo(point).Normalized());
  return true;

}
