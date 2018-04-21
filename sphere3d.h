#ifndef SPHERE3D_H_
#define SPHERE3D_H_

#include "point3d.h"
#include "ray3d.h"
#include "vec3d.h"

class Sphere3D
{
  public:
    Sphere3D(Point3D p, float r) : center_(p), radius_(r) {}

    std::string ToString() const;

    bool GetIntersection(Ray3D ray, Point3D& point, Vec3D& normal);

  private:
    Point3D center_;
    float radius_;
};

#endif