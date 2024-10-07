#pragma once
#include <iostream>

namespace astra {
class Vector {
  private:
    int size;
    int current_index;
    double* values;

  public:
    Vector(int size);
    Vector(const double values[], int size);
    Vector(const Vector& other);
    ~Vector();

    int get_size() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);

    Vector& operator<<(double val);
    Vector& operator,(double val);
    double operator*(const Vector& other) const;
    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    double operator[](int index) const;
    Vector operator^(const Vector& other) const;
    Vector& operator=(const Vector& other);
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
};
}
