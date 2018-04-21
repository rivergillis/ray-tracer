#ifndef PHONG_H_
#define PHONG_H_

#include "rgb.h"
#include "vec3d.h"
#include "point3d.h"

class Phong {
 public:
  Phong();
  ~Phong();

  void SetCamera(Point3D location);
  void SetLight(Rgb color, Vec3D dir);
  void SetObject(Rgb color, double a, double d, double s, double alpha);
  
  Rgb GetShade(Point3D location, Vec3D normal) const;

  Rgb GetSpecular(Point3D location, Vec3D normal) const;
  Rgb GetDiffuse(Vec3D normal) const;
  Rgb GetAmbient() const;
  Vec3D GetPerfectReflection(Vec3D normal) const;

 private:
  Point3D cam_location_;
  Rgb light_color_;
  Vec3D light_direction_;
  Rgb object_color_;

  double object_a_;
  double object_d_;
  double object_s_;
  double object_alpha_;
};

#endif // PHONG_H_