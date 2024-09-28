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
    double operator*(const Vector& other) const {
        if (this->size != other.size) {
            throw std::invalid_argument("Vectors must be of the same size for dot product.");
        }
        double result = 0;
        for (int i = 0; i < size; ++i) {
            result += this->values[i] * other.values[i];
        }
        return result;
    }
};
}
