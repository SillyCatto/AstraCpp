#pragma once
#include <iostream>

namespace astra {
class Vector {
  private:
    int size;
    int current_index;
    double* values;

  public:
    /**
     * @brief Constructs a vector of a specified size, initializing all elements
     * to zero.
     * @param size The size of the vector.
     * @throws astra::internals::exceptions::invalid_size if size is <= 0.
     */
    Vector(int size);

    /**
     * @brief Constructs a vector from an array of values.
     * @param values An array of values to initialize the vector.
     * @param size The size of the array and the vector.
     * @throws astra::internals::exceptions::invalid_size if size is <= 0.
     */
    Vector(const double values[], int size);

    /**
     * @brief Copy constructor for deep copying another vector.
     * @param other The vector to copy from.
     */
    Vector(const Vector& other);

    /**
     * @brief Destructor to free dynamically allocated memory.
     */
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
