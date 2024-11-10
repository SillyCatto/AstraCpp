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
     * @param size The size of the array and the vector.
     * @param values An array of values to initialize the vector.
     * @throws astra::internals::exceptions::invalid_size if size is <= 0.
     */
    Vector(int size, const double values[]);

    /**
     * @brief Copy constructor for deep copying another vector.
     * @param other The vector to copy from.
     */
    Vector(const Vector& other);

    Vector(std::initializer_list<double> values);

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
     * @brief Divides the vector by a scalar value.
     * @param scalar The scalar divisor.
     * @return A new vector divided by the scalar.
     * @throws astra::internals::exceptions::zero_division if scalar is zero.
     */
    Vector operator/(double scalar) const;

    /**
     * @brief Accesses an element at a specified index.
     * @param index The index of the element.
     * @return The value at the specified index.
     * @throws astra::internals::exceptions::index_out_of_range if index is out
     * of bounds.
     */
    double& operator[](int i);
    const double& operator()(int i) const;

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
     */
    double magnitude() const;

    /**
     * @brief Calculates the angle between two vectors in radians.
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @return The angle between the two vectors in radians.
     * @throws astra::internals::exceptions::vector_size_mismatch if the sizes
     * of the two vectors don't match.
     * @throws astra::internals::exceptions::invalid_argument if any of the
     * vectors has zero magnitude.
     */
    static double angle(const Vector& v1, const Vector& v2);

    /**
     * @brief Calculates the angle between two vectors in degrees.
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @return The angle between the two vectors in degrees.
     * @throws astra::internals::exceptions::vector_size_mismatch if the sizes
     * of the two vectors don't match.
     * @throws astra::internals::exceptions::invalid_argument if any of the
     * vectors has zero magnitude.
     */
    static double angle_deg(const Vector& v1, const Vector& v2);

    /**
     * @brief Computes the sum of all elements in the vector.
     * @return The sum of all elements in the vector.
     */
    double sum() const;

    /**
     * @brief Computes the avg of all elements in the vector.
     * @return The mean of all elements in the vector.
     */
    double avg() const;

    /**
     * @brief Computes the min of all elements in the vector.
     * @return The min of all elements in the vector.
     */
    double min() const;

    /**
     * @brief Computes the max of all elements in the vector.
     * @return The max of all elements in the vector.
     */
    double max() const;

    /**
     * @brief Normalizes the vector.
     * @return A new normalized vector.
     * @throws astra::internals::exceptions::zero_division if the vector has
     * zero magnitude.
     */
    Vector normalize() const;



    /**
     * @brief Multiplies each element of the vector by a scalar.
     * @param vec The vector to be scaled.
     * @param scalar The scalar value to multiply with each element of the
     * vector.
     * @return A new vector that is the result of scaling the original vector by
     * the scalar.
     */
    friend Vector operator*(const Vector& vec, double scalar);
    friend Vector operator*(double scalar, const Vector& vec);

    /**
     * @brief Overloads the stream insertion operator for printing the vector.
     * @param os The output stream.
     * @param vec The vector to output.
     * @return The output stream with the vector representation.
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
    friend std::istream& operator>>(std::istream& in, Vector& v);
};
}
