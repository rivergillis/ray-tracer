// Like Point3, but with Vector operations included

#ifndef VEC3_H_
#define VEC3_H_

#include <string>

class Vec3D {
 public:
  Vec3D(double x, double y, double z) : x_(x), y_(y), z_(z) {}
  double X() const { return x_; }
  double Y() const { return y_; }
  double Z() const { return z_; }

  void Set(const Vec3D& other);

  double Dot(const Vec3D& other) const;

  Vec3D Divide(double amount) const;
  Vec3D Multiply(double amount) const;
  
  Vec3D Add(const Vec3D& other) const;
  Vec3D Subtract(const Vec3D& other) const;

  double Magnitude() const;
  Vec3D Normalized() const;

  std::string ToString() const;

 private:
  double x_;
  double y_;
  double z_;
};

#endif // VEC3_H_