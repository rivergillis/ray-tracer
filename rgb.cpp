#include "rgb.h"

#include <random>
#include <iostream>
#include <sstream>

void Rgb::MakeRandom() {
  r_ = double(rand()) / RAND_MAX;
  g_ = double(rand()) / RAND_MAX;
  b_ = double(rand()) / RAND_MAX;
}

Rgb Rgb::Add(Rgb other) const {
  return {getR() + other.getR(),
          getG() + other.getG(),
          getB() + other.getB()};
}

Rgb Rgb::Multiply(double amount) const {
  return {getR() * amount,
          getG() * amount,
          getB() * amount};
}

Rgb Rgb::Multiply(Rgb other) const {
  return {getR() * other.getR(),
          getG() * other.getG(),
          getB() * other.getB()};
}

Rgb Rgb::Normalized() const {
  if (getR() <= 1 && getG() <= 1 && getB() <= 1) {
    if (getG() >= 0 && getG() >= 0 && getB() >= 0) {
      return *this;
    }
  }
  return {
    getR() / 255,
    getG() / 255,
    getB() / 255
  };
}

unsigned char Rgb::DenormR() const {
  return static_cast<unsigned char>(r_ * 255);
}
unsigned char Rgb::DenormG() const {
  return static_cast<unsigned char>(g_ * 255);
}
unsigned char Rgb::DenormB() const {
  return static_cast<unsigned char>(b_ * 255);
}


std::string Rgb::ToString(bool denormal) const {
  std::ostringstream os;
  if (denormal) {
    os << "RGB(" << int(r_ * 255) << ", " << int(g_ * 255) << ", " << int(b_ * 255) << ")";
  } else {
    os << "RGB(" << r_ << ", " << g_ << ", " << b_ << ")";
  }
  return os.str();
}