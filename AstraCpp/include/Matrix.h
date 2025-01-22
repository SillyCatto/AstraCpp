/**
 * @file Matrix.h
 * @brief Declaration of the Matrix class, which provides some basic matrix
 * operations for linear algebra.
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

namespace astra {

class Vector;

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
     * @param row The number of rows in the matrix.
     * @param col The number of columns in the matrix.
     * @throws astra::internals::exceptions::invalid_size if r or c is <= 0.
     */
    Matrix(int row, int col);

    /**
     * @brief Constructs a matrix from an array of values.
     * @param row The number of rows in the matrix.
     * @param col The number of columns in the matrix.
     * @param values An array of values to initialize the matrix.
     * @throws astra::internals::exceptions::invalid_size if r or c is <= 0.
     */
    Matrix(int row, int col, const double values[]);

    /**
     * @brief Constructs a matrix from an initializer list of values.
     * @param row The number of rows in the matrix.
     * @param col The number of columns in the matrix.
     * @param values An initializer list of values to initialize the matrix.
     * @throws astra::internals::exceptions::invalid_size if r or c is <= 0.
     */
    Matrix(int row, int col, std::initializer_list<double> values);

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
     * @brief Gives read-only access to a matrix entry at row i and column j
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
     * @brief Assign another matrix to this matrix (deep copy).
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
     * @brief Multiplies each element of the matrix by a scalar.
     * @param mat The matrix to multiply.
     * @param scalar The scalar value to multiply with each element of the
     * matrix.
     * @return A new matrix that is the result of multiplication of the original
     * matrix by the scalar.
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
     * @brief Outputs the matrix to an output stream.
     *
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
     *
     * @param in The input stream from which to read matrix values.
     * @param mat The matrix to populate with values from the input stream.
     * @return A reference to the input stream, allowing chaining of input
     * operations.
     */
    friend std::istream& operator>>(std::istream& in, Matrix& mat);


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
     * @brief Returns the sum of the principle diagonal elements of the matrix.
     * @return The trace of the matrix.
     * @throws astra::internals::exceptions::non_sqauare_matrix if the rows and
     * cols are not equal.
     */
    double trace() const;

    /**
     * @brief Computes the product of the principal diagonal elements of the
     * matrix.
     *
     *
     * @return The product of the diagonal elements.
     */
    double principal_prod() const;

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
     * @brief Checks if the matrix is singular.
     * @return True if the matrix is singular, false otherwise.
     */
    bool is_singular() const;

    /**
     * @brief Checks if the matrix is invertible.
     * @return True if the matrix is invertible, false otherwise.
     */
    bool is_invertible() const;


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
     * @brief Swaps two rows of the matrix in place.
     * @param row1 The index of the first row.
     * @param row2 The index of the second row.
     * @throws astra::internals::exceptions::index_out_of_range if i or j is
     * out of bounds.
    */
    void row_swap(int row1, int row2);

    /**
     * @brief Partially swaps two rows of the matrix up to a specified column
     * index.
     *
     * This function swaps the elements of `row1` and `row2` for all columns
     * from the beginning of the row up to (but not including) the specified
     * `limit_col`. It is primarily used during PLU decomposition to update the
     * L matrix when performing row swaps.
     *
     * @param row1 The index of the first row to be swapped.
     * @param row2 The index of the second row to be swapped.
     * @param limit_col The column index up to which the rows will be swapped.
     * @throws astra::internals::exceptions::index_out_of_range if `row1`,
     * `row2`, or `limit_col` are out of bounds.
     */
    void partial_row_swap(int row1, int row2, int limit_col);


    /**
     * @brief Swaps two columns of the matrix in place.
     * @param col1 The index of the first column.
     * @param col2 The index of the second column.
     * @throws astra::internals::exceptions::index_out_of_range if i or j is
     * out of bounds.
     */
    void col_swap(int col1, int col2);

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
     * @brief Horizontally concatenates another matrix to the right of the current matrix.
     *
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
     * @brief Extracts a submatrix from the matrix.
     *
     * @param r1 The starting row index of the submatrix. (inclusive)
     * @param c1 The starting column index of the submatrix. (inclusive)
     * @param r2 The ending row index of the submatrix. (inclusive)
     * @param c2 The ending column index of the submatrix. (inclusive)
     * @return Matrix A new matrix that is the submatrix defined by the
     * coordinates.
     * @throws astra::internals::exceptions::index_out_of_range if the specified indices are out of bounds or
     * astra::internals::exceptions::invalid_argument if the specified indices are invalid.
     */
    Matrix submatrix(int r1, int c1, int r2, int c2) const;


    /**
     * @brief Computes the row reduced echelon form of the matrix.
     *
     * @param tol (optional) The tolerance value for floating point comparison. Default is 1e-6.
     * @return Matrix The row reduced echelon form of the matrix.
     */
    Matrix rref(double tol = 1e-6) const;


    /**
     * @brief returns the ith row of the matrix in form of vector
     * 
     * @param i The index of the row to extract.
     * @return Vector The ith row of the matrix.
     * @throws astra::internals::exceptions::index_out_of_range if i is out of
     * bounds.
    */
    Vector get_row(int i) const;


    /**
     * @brief returns the jth column of the matrix in form of vector
     *
     * @param j The index of the column to extract.
     * @return Vector The jth column of the matrix.
     * @throws astra::internals::exceptions::index_out_of_range if j is out of
     * bounds.
     */
    Vector get_col(int j) const;

    /**
     * @brief Checks if the jth column is a pivot column.
     * @param j The index of the column to check.
     * @return True if the column is a pivot column, false otherwise.
     */
    bool is_pivot_col(int j) const;

    /**
     * @brief Checks if the ith row is a pivot row.
     * @param i The index of the row to check.
     * @return True if the row is a pivot row, false otherwise.
     */
    bool is_pivot_row(int i) const;

    /**
     * @brief Checks if the ith row has all zero elements.
     * @param i The index of the row to check.
     * @return True if the row has all zero elements, false otherwise.
     * @throws astra::internals::exceptions::index_out_of_range if i is out of
     * bounds.
     */
    bool is_zero_row(int i) const;

    /**
     * @brief Checks if the jth column has all zero elements.
     * @param j The index of the column to check.
     * @return True if the column has all zero elements, false otherwise.
     * @throws astra::internals::exceptions::index_out_of_range if j is out of
     * bounds.
     */
    bool is_zero_col(int j) const;

    /**
     * @brief Computes the rank of the matrix from its rref.
     * @return The rank of the matrix.
     */
    int rank() const;

    /**
     * @brief Computes the determinant of the matrix using PLU decomposition.
     *
     *
     * @throws astra::internals::exceptions::non_sqauare_matrix If the matrix is
     * not square.
     * @return double The determinant of the matrix.
     */
    double det() const;

    /**
     * @brief Computes the inverse of the matrix by Gauss-Jordan method.
     * @return Matrix The inverse of the matrix.
     * @throws astra::internals::exceptions::non_sqauare_matrix if the matrix is
     * not square.
     * @throws astra::internals::exceptions::singular_matrix if the matrix is
     * singular.
     */
    Matrix inv() const;

    /**
     * @brief Calculates the nullspace of a matrix from its RREF form
     *
     * @return A matrix containing the basis vectors of the nullspace. Each
     * column of the returned matrix represents a basis vector of the nullspace.
     *
     * @throws astra::internals::exceptions::invalid_size if the matrix is
     * invalid for RREF computation.
     *
     * @note If there are no free columns (i.e., the nullspace is trivial), the
     * returned matrix will have zero columns.
     */
    Matrix nullspace() const;

    /**
     * @brief Prints the matrix to the standard output with specified column
     * width.
     *
     *
     * @param width The width allocated for each matrix element when printed. (optional)
     */
    void print(int width = 7) const;
};
} // namespace astra
#endif // !__MATRIX_H__
