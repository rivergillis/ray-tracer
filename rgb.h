#ifndef RGB_H_
#define RGB_H_

#include <string>

class Rgb {
  public:
    Rgb(double r, double g, double b) : r_(r), g_(g), b_(b) {}

    Rgb Add(Rgb other) const;
    Rgb Multiply(double amount) const;
    Rgb Multiply(Rgb other) const;
    Rgb Normalized() const;

    double getR() const {
      return r_;
    }
    
    double getG() const {
      return g_;
    }

    double getB() const {
      return b_;
    }

    void setR(const double r) {
      r_ = r;
    }

    void setG(const double g) {
      g_ = g;
    }

    void setB(const double b) {
      b_ = b;
    }

    void MakeRandom();

    std::string ToString(bool denormal = false);

  private:
    double r_;
    double g_;
    double b_;
};

#endif // RGB_H_