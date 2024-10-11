/**
 * @file Vector.h
 * @brief Declaration of the Vector class, which provides some basic vector
 * operations for linear algebra.
 */

#pragma once
#include <iostream>

namespace astra {

/**
 * @class Vector
 * @brief A class for representing mathematical vectors with various operations.
 *
 * This class supports basic vector operations such as addition, subtraction,
 * scalar multiplication, dot product, cross product, and more.
 */
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

    /**
     * @brief Returns the size of the vector.
     * @return The number of elements in the vector.
     */
    int get_size() const;

    /**
     * @brief Adds a value to the vector via insertion operator for chaining.
     * @param val The value to add.
     * @return Reference to the updated vector.
     * @throws astra::internals::exceptions::init_out_of_range if insertion
     * exceeds vector size.
     */
    Vector& operator<<(double val);

    /**
     * @brief Adds a value to the vector using comma operator by chaining.
     * @param val The value to add.
     * @return Reference to the updated vector.
     */
    Vector& operator,(double val);

    /**
     * @brief Calculates the dot product with another vector.
     * @param other The vector to calculate the dot product with.
     * @return The dot product result.
     * @throws astra::internals::exceptions::vector_size_mismatch if sizes don't
     * match.
     */
    double operator*(const Vector& other) const;

    /**
     * @brief Multiplies the vector by a scalar value.
     * @param scalar The scalar value.
     * @return A new vector scaled by the scalar.
     */
    Vector operator*(double scalar) const;

    /**
     * @brief Divides the vector by a scalar value.
     * @param scalar The scalar divisor.
     * @return A new vector divided by the scalar.
     * @throws astra::internals::exceptions::zero_division if scalar is zero.
     */
    Vector operator/(double scalar) const;

     /**
     * @brief Adds this vector to another vector.
     * @param other The vector to add.
     * @return A new vector resulting from the addition.
     * @throws astra::internals::exceptions::vector_size_mismatch if sizes don't
     * match.
     */
    Vector operator+(const Vector& other) const;

     /**
     * @brief Subtracts another vector from this vector.
     * @param other The vector to subtract.
     * @return A new vector resulting from the subtraction.
     * @throws astra::internals::exceptions::vector_size_mismatch if sizes don't
     * match.
     */
    Vector operator-(const Vector& other) const;

    /**
     * @brief Accesses an element at a specified index.
     * @param index The index of the element.
     * @return The value at the specified index.
     * @throws astra::internals::exceptions::index_out_of_range if index is out
     * of bounds.
     */
    double operator[](int index) const;

    /**
     * @brief Calculates the cross product of a 3d vector with another 3d vector.
     * @param other The vector to calculate the cross product with.
     * @return A new vector as the cross product result.
     * @throws std::invalid_argument if either vector is not 3-dimensional.
     */
    Vector operator^(const Vector& other) const;

    /**
     * @brief Assigns another vector to this vector (deep copy).
     * @param other The vector to assign from.
     * @return Reference to this vector after assignment.
     */
    Vector& operator=(const Vector& other);

    /**
     * @brief Checks if this vector is equal to another vector.
     * @param other The vector to compare with.
     * @return True if vectors are equal, false otherwise.
     */

    bool operator==(const Vector& other) const;

    /**
     * @brief Checks if this vector is not equal to another vector.
     * @param other The vector to compare with.
     * @return True if vectors are not equal, false otherwise.
     */
    bool operator!=(const Vector& other) const;

    /**
     * @brief Computes the magnitude (length) of the vector.
     *
     * The magnitude of a vector is defined as the square root of the sum of the
     * squares of its components. For a vector v = [v1, v2, ..., vn], the
     * magnitude is calculated as:
     *
     *     magnitude = sqrt(v1^2 + v2^2 + ... + vn^2)
     *
     * @return The magnitude (length) of the vector as a double.
     * @throws astra::internals::exceptions::invalid_argument if the vector is empty or uninitialized.
     */
    double magnitude() const;

    /**
     * @brief Overloads the stream insertion operator for printing the vector.
     * @param os The output stream.
     * @param vec The vector to output.
     * @return The output stream with the vector representation.
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
};
}
