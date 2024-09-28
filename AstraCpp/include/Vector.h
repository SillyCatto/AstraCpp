#pragma once

namespace astra {
class Vector {
  private:
    int size;
    double* values;

  public:
    Vector(int size);
    ~Vector();
    int getSize() const;
    void print() const;

};
}
