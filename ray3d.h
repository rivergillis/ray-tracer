#ifndef RAY3D_H_
#define RAY3D_H_

#include "point3d.h"
#include "vec3d.h"

class Ray3D {
  public:
    Ray3D(Point3D p, Vec3D d) : point_(p), dir_(d.Normalized()) {}

    Ray3D(Point3D p1, Point3D p2) :
      point_(p1),
      dir_(p1.VecTo(p2).Normalized())
    {}

    Vec3D Dir() const { return dir_; }
    Point3D Origin() const { return point_; }

    Point3D GetSample(float t);

    std::string ToString() const;

  private:
    Point3D point_;
    Vec3D dir_;
};

#endif