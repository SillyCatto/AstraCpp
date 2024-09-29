#pragma once

namespace astra {
class Vector {
  private:
    int size;
    double* values;

  public:
    Vector(int size);
    Vector(const double values[], int size);
    Vector(const Vector& other);
    ~Vector();

    int get_size() const;
    bool is_null() const;
    void print() const;

    double operator*(const Vector& other) const;
};
}
