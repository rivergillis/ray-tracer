#include "phong.h"
#include <cmath>
#include <iostream>

Phong::Phong() : cam_location_(0, 0, 0), light_color_(0,0,0),
 light_direction_(0,0,0), object_color_(0,0,0), object_a_(0),
 object_d_(0), object_s_(0), object_alpha_(0) { }

Phong::~Phong() {}

void Phong::SetCamera(Point3D location) {
  cam_location_ = location;
}

void Phong::SetLight(Rgb color, Vec3D dir) {
  light_color_ = color;
  light_direction_ = dir;
}

void Phong::SetObject(Rgb color, double a, double d, double s, double alpha) {
  object_color_ = color;
  object_a_ = a;
  object_d_ = d;
  object_s_ = s;
  object_alpha_ = alpha;
}

Rgb Phong::GetAmbient() const {
  Rgb color = light_color_.Multiply(object_color_);
  std::cout << "\tAmbient: " << color.Multiply(object_a_).ToString() << std::endl;
  return color.Multiply(object_a_);
}

Rgb Phong::GetDiffuse(Vec3D normal) const {
  double dotted = light_direction_.Dot(normal);
  if (dotted < 0) {
    std::cout << "\tdiffuse ret 0" << std::endl;
    return {0, 0, 0};
  }
  Rgb color = light_color_.Multiply(object_color_);
  return color.Multiply(dotted * object_d_);
}

Vec3D Phong::GetPerfectReflection(Vec3D normal) const {
  double dotted = light_direction_.Dot(normal);
  if (dotted < 0) {
    std::cout << "\tperfrefl ret 0" << std::endl;
    return {0, 0, 0};
  }
  return normal.Multiply(2.0 * dotted).Subtract(light_direction_);
}


Rgb Phong::GetSpecular(Point3D location, Vec3D normal) const {
  Vec3D V = location.VecTo(cam_location_).Normalized();
  Vec3D R = GetPerfectReflection(normal).Normalized();
  double dotted = R.Dot(V);
  if (dotted < 0) {
    std::cout << "\tspec ret 0" << std::endl;
    return {0, 0, 0};
  }
  std::cout << "\tV: " << V.ToString() << std::endl;
  std::cout << "\tR: " << R.ToString() << std::endl;
  std::cout << "\tR dot V: " << dotted << std::endl;
  std::cout << "\t(R dot V)^alpha: " << std::pow(dotted, object_alpha_) << std::endl;

  return light_color_.Multiply(std::pow(dotted, object_alpha_) * object_s_);
}

Rgb Phong::GetShade(Point3D location, Vec3D normal) const {
  std::cout << "P[objcol: " << object_color_.ToString() << " objA: " << object_a_ << " objD: " << object_d_ << " objS " << object_s_ << " objAlpha: " << object_alpha_ << " loc: " << location.ToString() << " norm: " << normal.ToString() << " camloc: " << cam_location_.ToString() << " lightdir: " << light_direction_.ToString() << " lightcol " << light_color_.ToString() << std::endl; 
  return GetAmbient().Add(GetDiffuse(normal))
    .Add(GetSpecular(location, normal));
}