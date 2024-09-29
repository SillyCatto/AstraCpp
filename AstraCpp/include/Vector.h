#pragma once

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
    bool is_null() const;
    void print() const;

    Vector& operator<<(double val);
    Vector& operator,(double val);
    double operator*(const Vector& other) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    double operator[](int index) const;
};
}
