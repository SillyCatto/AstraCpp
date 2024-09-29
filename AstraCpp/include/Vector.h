#pragma once

namespace astra {
class Vector {
  private:
    int size;
    double* values;

  public:
    Vector(int size);
    Vector(const double values[], int size);
    ~Vector();

    int get_size() const;
    void print() const;

    double operator*(const Vector& other) const;
};
}
