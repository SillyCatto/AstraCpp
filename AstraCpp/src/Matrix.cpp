#include "pch.h"

#include "../include/Vector.h"
#include "../include/Matrix.h"
#include "../internals/Exceptions.h"
#include "../internals/Utils.h"
#include "../include/Decomposer.h"
#include "../internals/MathUtils.h"

#include <iostream>
#include <iomanip>

namespace astra {

Matrix::Matrix(int row, int col)
    : rows(row), cols(col), current_index(0), values(nullptr) {

    if (rows <= 0 || cols <= 0) {
        throw astra::internals::exceptions::invalid_size();
    }
    this->values = new double[rows * cols];

    for (int i = 0; i < (rows * cols); ++i) {
        this->values[i] = 0;
    }
}

Matrix::Matrix(int row, int col, const double values[])
    : rows(row), cols(col), current_index(0) {

    if (rows <= 0 || cols <= 0) {
        throw astra::internals::exceptions::invalid_size();
    }
    this->values = new double[rows * cols];

    for (int i = 0; i < (rows * cols); ++i) {
        this->values[i] = values[i];
    }
}

Matrix::Matrix(int row, int col, std::initializer_list<double> values)
    : rows(row), cols(col), current_index(0), values(new double[row * col]) {

    if (values.size() != static_cast<size_t>(row * col)) {
        throw astra::internals::exceptions::invalid_size();
    }

    int i = 0;
    for (double val : values) {
        if (i < row * col)
            this->values[i++] = val;
    }
}

Matrix::Matrix(const Matrix& other)
    : rows(other.rows), cols(other.cols), current_index(other.current_index),
      values(new double[other.rows * other.cols]) {
    for (int i = 0; i < rows * cols; ++i) {
        values[i] = other.values[i];
    }
}

Matrix::~Matrix() {
    delete[] values;
    values = nullptr;
}

Matrix& Matrix::operator<<(double val) {
    if (current_index < (rows * cols)) {
        values[current_index++] = val;
    }
    else {
        throw astra::internals::exceptions::init_out_of_range();
    }
    return *this;
}

Matrix &Matrix::operator,(double val) { return (*this << val); }

double& Matrix::operator()(int i, int j) {
    if (i >= rows || i < 0 || j >= cols || j < 0) {
        throw astra::internals::exceptions::index_out_of_range();
    }
    return values[i * cols + j];
}

const double& Matrix::operator()(int i, int j) const {
    if (i >= rows || i < 0 || j >= cols || j < 0) {
        throw astra::internals::exceptions::index_out_of_range();
    }
    return values[i * cols + j];
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw astra::internals::exceptions::matrix_size_mismatch();
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        result.values[i] = values[i] + other.values[i];
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw astra::internals::exceptions::matrix_size_mismatch();
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        result.values[i] = values[i] - other.values[i];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw astra::internals::exceptions::
            matrix_multiplication_size_mismatch();
    }

    Matrix result(rows, other.cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.values[i * result.cols + j] +=
                    values[i * cols + k] * other.values[k * other.cols + j];
            }
        }
    }

    return result;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    // resize if size dont match
    if (rows != other.rows || cols != other.cols) {
        delete[] values;
        rows = other.rows;
        cols = other.cols;
        values = new double[rows * cols];
    }

    // copy data
    for (int i = 0; i < rows * cols; ++i) {
        values[i] = other.values[i];
    }

    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }

    for (int i = 0; i < rows * cols; ++i) {
        if (values[i] != other.values[i]) {
            return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

void Matrix::replace(double old_val, double new_val) {
    for (int i = 0; i < rows * cols; ++i) {
        if (values[i] == old_val) {
            values[i] = new_val;
        }
    }
}

double Matrix::sum() const {
    double total = 0.0;
    for (int i = 0; i < rows * cols; ++i) {
        total += values[i];
    }
    return total;
}

double Matrix::prod() const {
    double total = 1.0;
    for (int i = 0; i < rows * cols; ++i) {
        total *= values[i];
    }
    return total;
}

double Matrix::trace() const {
    if (!is_square()) {
        throw astra::internals::exceptions::non_square_matrix();
    }
    double sum = 0.0;
    for (int i = 0; i < rows; ++i) {
        sum += values[i * cols + i];
    }
    return sum;
}

double astra::Matrix::principal_prod() const {
    if (!is_square()) {
        throw astra::internals::exceptions::non_square_matrix();
    }
    double prod = 1.0;
    for (int i = 0; i < rows; ++i) {
        prod *= values[i * cols + i];
    }
    return prod;
}

double Matrix::avg() const {
    if (rows == 0 || cols == 0) {
        throw astra::internals::exceptions::invalid_size();
    }

    double sum = 0.0;
    for (int i = 0; i < rows * cols; ++i) {
        sum += values[i];
    }
    return sum / (rows * cols);
}

double Matrix::min() const {
    double minVal = values[0];
    for (int i = 0; i < rows * cols; ++i) {
        if (values[i] < minVal) {
            minVal = values[i];
        }
    }
    return minVal;
}

double Matrix::max() const {
    double maxVal = values[0];
    for (int i = 0; i < rows * cols; ++i) {
        if (values[i] > maxVal) {
            maxVal = values[i];
        }
    }
    return maxVal;
}

bool Matrix::is_square() const { return rows == cols; }

bool Matrix::is_identity() const {
    if (!is_square()) {
        return false;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == j) { // diagonal
                if (!internals::mathutils::nearly_equal(values[i * cols + j],
                                                        1.0)) {
                    return false;
                }
            }
            else { // non-diagonal
                if (!internals::mathutils::nearly_equal(values[i * cols + j],
                                                        0.0)) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Matrix::is_symmetric() const {
    if (!is_square()) {
        return false;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!internals::mathutils::nearly_equal(values[i * cols + j],
                                                    values[j * cols + i])) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::is_diagonal() const {
    if (!is_square()) {
        return false;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i != j && !internals::mathutils::nearly_equal(
                              values[i * cols + j], 0.0)) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::is_upper_triangular() const {
    if (!is_square()) {
        return false;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < i; ++j) {
            if (!internals::mathutils::nearly_equal(values[i * cols + j],
                                                    0.0)) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::is_lower_triangular() const {
    if (!is_square()) {
        return false;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = i + 1; j < cols; ++j) {
            if (!internals::mathutils::nearly_equal(values[i * cols + j],
                                                    0.0)) {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::is_triangular() const {
    return is_lower_triangular() || is_upper_triangular();
}

bool Matrix::is_zero() const {
    for (int i = 0; i < rows * cols; ++i) {
        if (!internals::mathutils::nearly_equal(values[i], 0.0)) {
            return false;
        }
    }
    return true;
}

Matrix Matrix::identity(int n) {
    if (n <= 0) {
        throw astra::internals::exceptions::invalid_size();
    }

    Matrix identity(n, n);
    for (int i = 0; i < n; ++i) {
        identity(i, i) = 1.0;
    }

    return identity;
}

void Matrix::transpose() {
    if (is_square()) {
        // sqaure
        for (int i = 0; i < rows; ++i) {
            for (int j = i + 1; j < cols; ++j) {
                astra::internals::utils::swap(values[i * cols + j],
                                              values[j * cols + i]);
            }
        }
    }
    else {
        // rectangular
        double* transposedValues = new double[rows * cols];
        int newRows = cols;
        int newCols = rows;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                transposedValues[j * newCols + i] = values[i * cols + j];
            }
        }

        delete[] values;
        values = transposedValues;
        rows = newRows;
        cols = newCols;
    }
}

void Matrix::row_swap(int row1, int row2) {
    if (row1 >= rows || row2 >= rows || row1 < 0 || row2 < 0) {
        throw astra::internals::exceptions::index_out_of_range();
    }

    for (int k = 0; k < cols; ++k) {
        astra::internals::utils::swap(values[row1 * cols + k],
                                      values[row2 * cols + k]);
    }
}

void Matrix::partial_row_swap(int row1, int row2, int limit_col) {
    if (row1 >= rows || row2 >= rows || row1 < 0 || row2 < 0 ||
        limit_col >= cols || limit_col < 0) {
        throw astra::internals::exceptions::index_out_of_range();
    }

    for (int k = 0; k < limit_col; k++) {
        astra::internals::utils::swap(values[row1 * cols + k],
                                      values[row2 * cols + k]);
    }
}

void Matrix::col_swap(int col1, int col2) {
    if (col1 >= cols || col2 >= cols || col1 < 0 || col2 < 0) {
        throw astra::internals::exceptions::index_out_of_range();
    }

    for (int k = 0; k < rows; ++k) {
        astra::internals::utils::swap(values[k * cols + col1],
                                      values[k * cols + col2]);
    }
}

void Matrix::clear() {
    for (int i = 0; i < rows * cols; ++i) {
        values[i] = 0.0;
    }
}

void astra::Matrix::fill(double val) {
    for (int i = 0; i < rows * cols; ++i) {
        values[i] = val;
    }
}

void astra::Matrix::resize(int r, int c) {
    if (r <= 0 || c <= 0) {
        throw astra::internals::exceptions::invalid_size();
    }

    if (r == rows && c == cols) {
        return;
    }

    double* newValues = new double[r * c];
    delete[] values;
    values = newValues;
    rows = r;
    cols = c;
    fill(0);
}

void Matrix::join(const Matrix& other) {
    int num_row_1 = this->rows;
    int num_col_1 = this->cols;
    int num_row_2 = other.rows;
    int num_col_2 = other.cols;

    if (num_row_1 != num_row_2) {
        throw astra::internals::exceptions::matrix_join_size_mismatch();
    }

    double* join_values = new double[num_row_1 * (num_col_1 + num_col_2)];

    int linear_ind, join_linear_ind;

    for (int i = 0; i < num_row_1; ++i) {
        for (int j = 0; j < (num_col_1 + num_col_2); ++j) {
            join_linear_ind = (i * (num_col_1 + num_col_2)) + j;

            // if j is in lhs, get data from there
            if (j < num_col_1) {
                linear_ind = (i * num_col_1) + j;
                join_values[join_linear_ind] = values[linear_ind];
            }
            // if j is in rhs, get data from there
            else {
                linear_ind = (i * num_col_2) + (j - num_col_1);
                join_values[join_linear_ind] = other.values[linear_ind];
            }
        }
    }

    this->cols = num_col_1 + num_col_2;
    this->rows = num_row_1;

    double* new_val = new double[rows * cols];
    delete[] values;
    values = new_val;

    for (int i = 0; i < rows * cols; ++i) {
        values[i] = join_values[i];
    }

    delete[] join_values;
    join_values = nullptr;
}

Matrix Matrix::submatrix(int r1, int c1, int r2, int c2) const {
    if (r1 < 0 || r1 >= rows || r2 < 0 || r2 >= rows || c1 < 0 || c1 >= cols ||
        c2 < 0 || c2 >= cols) {
        throw astra::internals::exceptions::index_out_of_range();
    }
    if (r1 > r2 || c1 > c2) {
        throw astra::internals::exceptions::invalid_argument();
    }

    int new_rows = r2 - r1 + 1;
    int new_cols = c2 - c1 + 1;
    Matrix submat(new_rows, new_cols);

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            submat(i, j) = values[(r1 + i) * cols + (c1 + j)];
        }
    }
    return submat;
}

Matrix Matrix::rref(double tol) const {
    int r = 0;
    int pivot_row = -1;
    int pivot_col = -1;
    double pivot_val = 0.0;
    double factor = 0.0;

    Matrix rref(*this);

    for (int c = 0; c < cols; c++) {
        pivot_row = -1;

        for (int i = r; i < rows; i++) {
            if (internals::mathutils::abs(rref(i, c)) > tol) {
                pivot_row = i;
                break;
            }
        }

        // pivot not found
        if (pivot_row == -1) {
            continue;
        }

        // swap rows to move selected pivot to current row
        for (int k = 0; k < cols; ++k) {
            astra::internals::utils::swap(rref.values[r * cols + k],
                                          rref.values[pivot_row * cols + k]);
        }

        // normalize the pivot row
        pivot_val = rref(r, c);
        if (internals::mathutils::abs(pivot_val) > tol) {
            for (int i = 0; i < cols; i++) {
                rref(r, i) = rref(r, i) / pivot_val;
            }
        }
        

        // eliminate entries below pivot
        for (int i = r + 1; i < rows; i++) {
            factor = rref(i, c);
            for (int j = 0; j < cols; j++) {
                rref(i, j) = rref(i, j) - factor * rref(r, j);
            }
        }

        r++; // move to next row
    }

    // backward elimination
    for (int i = r - 1; i >= 0; i--) {
        pivot_col = -1;

        for (int c = 0; c < cols; c++) {
            if (internals::mathutils::abs(rref(i, c)) > tol) {
                pivot_col = c;
                break;
            }
        }

        // pivot not found
        if (pivot_col == -1) {
            continue;
        }

        // eliminate entries above pivot
        for (int j = i - 1; j >= 0; j--) {
            factor = rref(j, pivot_col);
            for (int k = 0; k < cols; k++) {
                rref(j, k) = rref(j, k) - factor * rref(i, k);
            }
        }
    }

    // stabilize the near-zero entry to exactly zero
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (internals::mathutils::abs(rref(i, j)) < tol) {
                rref(i, j) = 0.0;
            }
        }
    }

    return rref;
}

Vector Matrix::get_row(int i) const {
    if (i < 0 || i >= rows) {
        throw astra::internals::exceptions::index_out_of_range();
    }
    
    Vector row(cols);
    for (int j = 0; j < cols; ++j) {
        row[j] = values[i * cols + j];
    }
    
    return row;
}

Vector Matrix::get_col(int j) const {
    if (j < 0 || j >= cols) {
        throw astra::internals::exceptions::index_out_of_range();
    }

    Vector col(rows);
    for (int i = 0; i < rows; ++i) {
        col[i] = values[i * cols + j];
    }
    return col;
}

bool Matrix::is_pivot_col(int j) const {
    if (j < 0 || j >= cols) {
        throw astra::internals::exceptions::index_out_of_range();
    }
    Matrix rref_matrix = this->rref();
    for (int i = 0; i < rows; ++i) {
        if (internals::mathutils::nearly_equal(rref_matrix(i, j), 1.0)) {
            // Ensuring if it's the leading entry in this row
            for (int k = 0; k < j; ++k) {
                if (!internals::mathutils::nearly_equal(rref_matrix(i, k), 0.0)) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool Matrix::is_pivot_row(int i) const {
    if (i < 0 || i >= rows) {
        throw astra::internals::exceptions::index_out_of_range();
    }
    Matrix rref_matrix = this->rref();

    // Checking if this row contains a pivot
    for (int j = 0; j < cols; ++j) {
        if (internals::mathutils::nearly_equal(rref_matrix(i, j), 1.0)) {
            // Ensuring if it's the only non-zero value in its column
            for (int k = 0; k < rows; ++k) {
                if (k != i &&
                    !internals::mathutils::nearly_equal(rref_matrix(k, j), 0.0)) {
                    return false; // Another row has a non-zero in this column
                }
            }
            return true; // Found a valid pivot
        }
    }
    return false; // No pivot in this row
}

bool Matrix::is_zero_row(int i) const {
    if (i < 0 || i >= rows) {
        throw astra::internals::exceptions::index_out_of_range();
    }
    for (int j = 0; j < cols; ++j) {
        if (!internals::mathutils::nearly_equal(values[i * cols + j], 0.0)) {
            return false;
        }
    }
    return true;
}

bool Matrix::is_zero_col(int j) const { 
    if (j < 0 || j >= cols) {
        throw astra::internals::exceptions::index_out_of_range();
    }
    for (int i = 0; i < rows; ++i) {
        if (!internals::mathutils::nearly_equal(values[i * cols + j], 0.0)) {
            return false;
        }
    }
    return true;
}

int Matrix::rank() const {
    Matrix rref_matrix = this->rref(); 
    int rank = 0;

    for (int i = 0; i < rows; ++i) {
        // Checking if the row is non-zero
        bool non_zero_row = false;
        for (int j = 0; j < cols; ++j) {
            if (internals::mathutils::abs(rref_matrix(i, j)) >
                1e-6) { // Avoiding floating-point errors
                non_zero_row = true;
                break;
            }
        }
        if (non_zero_row) {
            rank++;
        }
    }

    return rank;
}

double Matrix::det() const {
    if (!is_square()) {
        throw astra::internals::exceptions::non_square_matrix();
    }
    auto plu = astra::Decomposer::palu(*this);

    double det = plu.U.principal_prod();

    // for even no. of swaps determinant is +ve,
    // for odd swaps it is -ve
    det *= (plu.swaps % 2 == 0) ? 1 : -1;

    return det;
}

bool Matrix::is_singular() const {
    return internals::mathutils::nearly_equal(det(), 0.0);
}

bool Matrix::is_invertible() const { 
    if (!is_square()) {
        return false;
    }
    if (is_singular()) {
        return false;
    }
    return true;
}

Matrix Matrix::inv() const {
    if (!is_square()) {
        throw astra::internals::exceptions::non_square_matrix();
    }
    if (is_singular()) {
        throw astra::internals::exceptions::singular_matrix();
    }
    // taking an identity matrix
    Matrix inverse = Matrix::identity(rows);
    // making copy of the given matrix
    Matrix mat_copy(*this);

    // making mat_copy to upper triangular form
    for (int i = 0; i < rows; i++) {
        // taking the diagonal elements
        double current_val = mat_copy(i, i);

        for (int j = i + 1; j < rows; j++) {
            // to eleminate the ith element, how should we add ith row to jth
            // row
            double mult = -mat_copy(j, i) / current_val;

            for (int k = 0; k < rows; k++) {
                // eleminating the ith element and updating the inverse
                // accordingly
                mat_copy(j, k) += mult * mat_copy(i, k);
                inverse(j, k) += mult * inverse(i, k);
            }
        }
    }

    // making mat_copy to diagonal form
    for (int i = rows - 1; i >= 0; i--) {
        double current_val = mat_copy(i, i);

        for (int j = i - 1; j >= 0; j--) {
            double mult = -mat_copy(j, i) / current_val;

            for (int k = 0; k < rows; k++) {
                mat_copy(j, k) += mult * mat_copy(i, k);
                inverse(j, k) += mult * inverse(i, k);
            }
        }
    }

    // scaling to identity
    for (int i = 0; i < rows; i++) {

        double current_val = mat_copy(i, i);
        mat_copy(i, i) /= current_val;

        for (int j = 0; j < rows; j++) {
            inverse(i, j) /= current_val;
        }
    }

    return inverse;
}

Matrix operator*(const Matrix& mat, double scalar) {

    int rows = mat.num_row();
    int cols = mat.num_col();

    Matrix result(rows, cols);

    for (int i = 0; i < rows * cols; ++i) {
        result.values[i] = mat.values[i] * scalar;
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& mat) {
    return mat * scalar;
}

Matrix operator/(const Matrix& mat, double scalar) {
    if (internals::mathutils::nearly_equal(scalar, 0.0)) {
        throw astra::internals::exceptions::zero_division();
    }

    int rows = mat.num_row();
    int cols = mat.num_col();

    Matrix result(rows, cols);

    for (int i = 0; i < rows * cols; ++i) {
        result.values[i] = mat.values[i] / scalar;
    }

    return result;
}

int Matrix::num_row() const { return rows; }
int Matrix::num_col() const { return cols; }

void Matrix::print(int width) const {
    for (int i = 0; i < rows; ++i) {
        std::cout << "[";
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(width) << values[i * cols + j];
            if (j < cols - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat.rows; ++i) {
        os << "[";
        for (int j = 0; j < mat.cols; ++j) {
            os << std::setw(8) << mat.values[i * mat.cols + j];
            if (j < mat.cols - 1)
                os << ", ";
        }
        os << "]" << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& in, Matrix& mat) {
    int size = mat.rows * mat.cols;
    int i = 0;
    while (i < size && in >> mat.values[i]) {
        ++i;
    }

    for (; i < size; ++i) {
        mat.values[i] = 0.0;
    }
    return in;
}
} // namespace astra
