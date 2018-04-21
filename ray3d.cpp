#include "ray3d.h"
#include "point3d.h"
#include <sstream>

std::string Ray3D::ToString() const {
  std::ostringstream os;
  os << "Ray3D @(" << point_.ToString() << ") to " << dir_.ToString();
  return os.str();
}

Point3D Ray3D::GetSample(float t) {
  return point_.Add(dir_.Multiply(t));
}