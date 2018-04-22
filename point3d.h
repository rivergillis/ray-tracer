// Author: (Jameson) River Gillis
//
// Point3D is a simple (x,y,z) point pairing data type.
// It is mutable to allow for the resizing of points.

#ifndef Point3D_H_
#define Point3D_H_

#include "vec3d.h"
#include <string>

class Point3D {
  public:
    Point3D(double x, double y, double z = 0.0) : x_(x), y_(y), z_(z) {}

    Point3D Add(Vec3D other) const;
    Point3D Subtract(Point3D other) const;

    double getX() const {
      return x_;
    }
    
    double getY() const {
      return y_;
    }

    double getZ() const {
      return z_;
    }

    void setX(const double x) {
      x_ = x;
    }

    void setY(const double y) {
      y_ = y;
    }

    void setZ(const double z) {
      z_ = z;
    }

    double DistanceTo(Point3D other);

    Vec3D VecTo(Point3D other) const;

    std::string ToString() const;

  private:
    double x_;
    double y_;
    double z_;
};

#endif // Point3D_H_