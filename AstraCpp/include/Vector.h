#pragma once

namespace astra {
class Vector {
  private:
    int size;
    double* values;

  public:
    Vector(int size);
    Vector(const double values[]);
    ~Vector();
    int getSize() const;
    void print() const;

};
}
