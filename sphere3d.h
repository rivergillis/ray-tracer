#ifndef SPHERE3D_H_
#define SPHERE3D_H_

#include "point3d.h"
#include "ray3d.h"
#include "vec3d.h"
#include "rgb.h"

class Sphere3D
{
  public:
    Sphere3D(Point3D p, float r, double a, double d, double s, double alpha, Rgb color) : center_(p), radius_(r), a_(a), d_(d), s_(s), alpha_(alpha), color_(color) {}

    std::string ToString() const;

    bool GetIntersection(Ray3D ray, Point3D& point, Vec3D& normal) const;

  private:
    Point3D center_;
    float radius_;

    double a_;
    double d_;
    double s_;
    double alpha_;
    Rgb color_;
};

#endif