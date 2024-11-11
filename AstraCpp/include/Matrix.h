/**
 * @file Matrix.h
 * @brief Declaration of the Matrix class, which provides some basic matrix
 * operations for linear algebra.
 */

#pragma once
#include <iostream>

namespace astra {

/**
 * @class Matrix
 * @brief A class for representing mathematical matrices with various operations.
 *
 * This class supports basic matrix operations such as addition, subtraction,
 * scalar multiplication, matrix multiplication, transpose and more.
 */
class Matrix {
  private:
    int rows;
    int cols;
    int current_index;
    double* values;

  public:
    /**
     * @brief Constructs a matrix of a specified size, initializing all elements
     * to zero.
     * @param r The number of rows in the matrix.
     * @param c The number of columns in the matrix.
     * @throws astra::internals::exceptions::invalid_size if r or c is <= 0.
     */
    Matrix(int r, int c);

    /**
     * @brief Constructs a matrix from an array of values.
     * @param r The number of rows in the matrix.
     * @param c The number of columns in the matrix.
     * @param values An array of values to initialize the matrix.
     * @throws astra::internals::exceptions::invalid_size if r or c is <= 0.
     */
    Matrix(int r, int c, const double values[]);

    /**
     * @brief Constructs a matrix from an initializer list of values.
     * @param r The number of rows in the matrix.
     * @param c The number of columns in the matrix.
     * @param values An initializer list of values to initialize the matrix.
     * @throws astra::internals::exceptions::invalid_size if r or c is <= 0.
     */
    Matrix(int r, int c, std::initializer_list<double> values);

    /**
     * @brief Copy constructor for deep copying another matrix.
     * @param other The matrix to copy from.
     */
    Matrix(const Matrix& other);

    /**
     * @brief Destructor to free dynamically allocated memory.
     */
    ~Matrix();

    /**
     * @brief Overloaded operator to insert a value into the matrix.
     * @param val The value to insert.
     * @return A reference to the matrix object.
     * @throws astra::internals::exceptions::init_out_of_range if current index
     * is >= row or col.
     */
    Matrix& operator<<(double val);

    /**
     * @brief Overloaded operator to insert a value into the matrix.
     * @param val The value to insert.
     * @return A reference to the matrix object.
     */
    Matrix& operator,(double val);

    /**
     * @brief Overloaded operator to access a value in the matrix.
     * @param i The row index.
     * @param j The column index.
     * @return A reference to the value at the specified row and column.
     * @throws astra::internals::exceptions::index_out_of_range if i or j is
     * out of bounds.
     */
    double& operator()(int i, int j);
    
    /**
     * @brief Accesses a matrix element at the specified row and column in a
     * read-only manner.
     *
     * This function provides read-only access to elements within the matrix,
     * allowing retrieval of an element located at the given row and column. The
     * function performs bounds-checking to ensure the indices are within valid
     * limits and throws an exception if the indices are out of range.
     *
     * @param i The row index of the desired element.
     * @param j The column index of the desired element.
     * @return A constant reference to the matrix element at the specified
     * position.
     * @throws astra::internals::exceptions::index_out_of_range if the indices
     * `i` or `j` are outside the valid range of rows or columns.
     */
    const double& operator()(int i, int j) const;


    /**
     * @brief Returns the number of rows in the matrix.
     * @return The number of rows.
     */
    int num_row() const;

    /**
     * @brief Returns the number of columns in the matrix.
     * @return The number of columns.
     */
    int num_col() const;


    /**
     * @brief Overloaded operator to add two matrices.
     * @param other The matrix to add.
     * @return The sum of the two matrices.
     * @throws astra::internals::exceptions::matrix_size_mismatch if the
     * matrices are not of the same size.
     */
    Matrix operator+(const Matrix& other) const;

    /**
     * @brief Overloaded operator to subtract two matrices.
     * @param other The matrix to subtract.
     * @return The difference of the two matrices.
     * @throws astra::internals::exceptions::matrix_size_mismatch if the
     * matrices are not of the same size.
     */
    Matrix operator-(const Matrix& other) const;

    /**
     * @brief Overloaded operator to multiply two matrices.
     * @param other The matrix to multiply.
     * @return The product of the two matrices.
     * @throws astra::internals::exceptions::matrix_multiplication_size_mismatch
     * if the number of columns in the current matrix does not match the number
     * of rows in the `other` matrix.
     */
    Matrix operator*(const Matrix& other) const;

    /**
     * @brif Assign another matrix to this matrix (deep copy).
     * @param other The matrix to assign from.
     * @return Reference to this matrix after assignment.
     */
    Matrix& operator=(const Matrix& other);

    /**
     * @brief Checkes if two matrices are equal.
     * @param other The matrix to compare with.
     * @return True if the matrices are equal, false otherwise.
     */
    bool operator==(const Matrix& other) const;

    /**
     * @brief Checkes if two matrices are not equal.
     * @param other The matrix to compare with.
     * @return True if the matrices are not equal, false otherwise.
     */
    bool operator!=(const Matrix& other) const;

    /**
     * @brief Replace all occurrences of a value with another value.
     * @param old_val The value to replace.
     * @param new_val The value to replace with
     * @note does nothing if the the value is not in the matrix
    */
    void replace(double old_val, double new_val);


    /**
     * @brief Returns the sum of all elements in the matrix.
     * @return The sum of all elements in the matrix.
     */
    double sum() const;

    /**
     * @brief Returns the product of all elements in the matrix.
     * @return The product of all elements in the matrix.
     */
    double prod() const;

    /**
     * @brief Returns the product of the principle diagonal elements of the matrix.
     * @return The trace of the matrix.
     * @throws astra::internals::exceptions::invalid_argument if the rows and
     * cols are not equal.
     */
    double trace() const;

    /**
     * @brief Returns the average of all elements in the matrix.
     * @return The average of all elements in the matrix.
     * @throws astra::internals::exceptions::invalid_size if the matrix has zero 
     * row or column.
     */
    double avg() const;


    /**
     * @brief Returns the minimum value in the matrix.
     * @return The minimum value in the matrix.
     */
    double min() const;

    /**
     * @brief Returns the maximum value in the matrix.
     * @return The maximum value in the matrix.
     */
    double max() const;


    /**
     * @brief Checks if this matrix is square.
     * @return True if the matrix is square, false otherwise.
     */
    bool is_square() const;

    /**
     * @brief Checks if this matrix is rectangular.
     * @return True if the matrix is rectangular, false otherwise.
     */
    bool is_rectangular() const;

    /**
     * @brief Checks if this matrix is identity matrix.
     * @return True if the matrix is identity matrix, false otherwise.
     */
    bool is_identity() const;

    /**
     * @brief Checks if this matrix is symmetric.
     * @return True if the matrix is symmetric, false otherwise.
     */
    bool is_symmetric() const;

    /**
     * @brief Checks if this matrix is diagonal.
     * @return True if the matrix is diagonal, false otherwise.
     */
    bool is_diagonal() const;

    /**
     * @brief Checks if this matrix is upper triangular.
     * @return True if the matrix is upper triangular, false otherwise.
     */
    bool is_upper_triangular() const;

    /**
     * @brief Checks if this matrix is lower triangular.
     * @return True if the matrix is lower triangular, false otherwise.
     */
    bool is_lower_triangular() const;

    /**
     * @brief Checks if this matrix is triangular.
     * @return True if the matrix is triangular, false otherwise.
     */
    bool is_triangular() const;

    /**
     * @brief Checks if all elements in the matrix are zero.
     * @return True if all elements are zero, false otherwise.
    */
    bool is_zero() const;


    /**
     * @brief Creates an identity matrix of a specified size.
     * @param n The row and column of the identity matrix.
     * @return The identity matrix.
     * @throws astra::internals::exceptions::invalid_size if n is <= 0.
    */
    static Matrix identity(int n);


    /**
     * @brief Transposes the matrix in place.
     */
    void transpose();

    /**
     * @brief Swaps two rows of the matrix.
     * @param i The index of the first row.
     * @param j The index of the second row.
     * @throws astra::internals::exceptions::index_out_of_range if i or j is
     * out of bounds.
    */
    void row_swap(int i, int j);


    /**
     * @brief Makes all elements of the matrix zero.
    */
    void clear();

    /**
     * @brief Fills the matrix with a specified value.
     * @param val The value to fill the matrix with.
     */
    void fill(double val);


    /**
     * @brief Resizes the matrix to a new size with all elements set to 0.
     * @param r The new number of rows.
     * @param c The new number of columns.
     * @throws astra::internals::exceptions::invalid_size if r or c is <= 0.
     */
    void resize(int r, int c);

    /**
     * @brief Concatenates another matrix to the right of the current matrix.
     *
     * This function horizontally joins the `other` matrix to the current matrix
     * (`this`), effectively increasing the number of columns. Both matrices
     * must have the same number of rows. After the operation, the current
     * matrix (`this`) will have its columns expanded by the number of columns
     * in the `other` matrix, and the `other` matrix remains unchanged.
     *
     * @param other The matrix to be joined to the right of the current matrix.
     * @throws astra::internals::exceptions::matrix_join_size_mismatch if the
     * number of rows in the current matrix does not match the number of rows in
     * the `other` matrix.
     *
     * @note This operation modifies the current matrix in-place.
     */
    void join(const Matrix& other);


    /**
     * @brief Multiplies each element of the matrix by a scalar.
     * @param mat The matrix to multiply.
     * @param scalar The scalar value to multiply with each element of the
     * matrix.
     * @return A new matrix that is the result of multiplication of the original matrix 
     * by the scalar.
     */
    friend Matrix operator*(const Matrix& mat, double scalar); 
    friend Matrix operator*(double scalar, const Matrix& mat); 
    

    /**
     * @brief Divides each element of the matrix by a scalar.
     * @param mat The matrix to divide.
     * @param scalar The scalar value to divide each element of the matrix by.
     * @return A new matrix that is the result of division of the original
     * matrix by the scalar.
     * @throws astra::internals::exceptions::zero_division if scalar is zero.
     */
    friend Matrix operator/(const Matrix& mat, double scalar);

    /**
     * @brief Prints the matrix to the standard output with specified column
     * width.
     *
     * This function displays the matrix in a formatted layout, where each row
     * is printed on a new line with elements separated by commas. Each element
     * occupies a specified width, aligning the output for improved readability.
     *
     * @param width The width allocated for each matrix element when printed.
     */
    void print(int width = 7) const;

    /**
     * @brief Outputs the matrix to an output stream.
     *
     * This operator overloads the << operator, allowing matrices to be
     * displayed through an output stream such as `std::cout`. The function
     * formats each row of the matrix with elements separated by commas and
     * enclosed in square brackets.
     *
     * @param os The output stream to which the matrix will be sent.
     * @param mat The matrix to output.
     * @return A reference to the output stream, allowing chaining of output
     * operations.
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

    /**
     * @brief Reads matrix values from an input stream.
     *
     * This operator overloads the >> operator, enabling input of matrix
     * elements from an input stream such as `std::cin`. Elements are read
     * sequentially, filling the matrix in row-major order. If there are fewer
     * elements than required, remaining entries are filled with zero. Excess
     * elements are ignored.
     *
     * @param in The input stream from which to read matrix values.
     * @param mat The matrix to populate with values from the input stream.
     * @return A reference to the input stream, allowing chaining of input
     * operations.
     */
    friend std::istream& operator>>(std::istream& in, Matrix& mat);
};
} // namespace astra
