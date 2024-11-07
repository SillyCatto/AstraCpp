#include "pch.h"
#include "Matrix.h"
#include "Exceptions.h"
#include "Utils.h"

#include <iostream>
#include <iomanip>

using namespace astra;

Matrix::Matrix(int r, int c)
    : rows(r), cols(c), current_index(0), values(nullptr) {

    if (rows <= 0 || cols <= 0) {
        throw astra::internals::exceptions::invalid_size();
    }
    this->values = new double[rows * cols];

    for (int i = 0; i < (rows * cols); ++i) {
        this->values[i] = 0;
    }
}

Matrix::Matrix(int r, int c, const double values[])
    : rows(r), cols(c), current_index(0) {

    if (rows <= 0 || cols <= 0) {
        throw astra::internals::exceptions::invalid_size();
    }
    this->values = new double[rows * cols];

    for (int i = 0; i < (rows * cols); ++i) {
        this->values[i] = values[i];
    }
}

Matrix::Matrix(int r, int c, std::initializer_list<double> values)
    : rows(r), cols(c), current_index(0), values(new double[r * c]) {

    if (values.size() != static_cast<size_t>(r * c)) {
        throw astra::internals::exceptions::invalid_size();
    }

    int i = 0;
    for (double val : values) {
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


Matrix::~Matrix() { delete[] values; }

Matrix& Matrix::operator<<(double val) {
    if (current_index < (rows * cols)) {
        values[current_index++] = val;
    }
    else {
        throw astra::internals::exceptions::init_out_of_range();
    }
    return *this;
}

Matrix& Matrix::operator,(double val) { return (*this << val); }

double& Matrix::operator()(int i, int j) { 
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

bool astra::Matrix::operator!=(const Matrix& other) const { 
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

double Matrix::principal_prod() const {
    if (rows != cols) {
        throw astra::internals::exceptions::invalid_argument();
    }
    double product = 1.0;
    for (int i = 0; i < rows; ++i) {
        product *= values[i * cols + i];
    }
    return product;
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

bool Matrix::is_zero() const {
    for (int i = 0; i < rows * cols; ++i) {
        if (values[i] != 0.0) {
            return false;
        }
    }
    return true;
}

Matrix Matrix::id(int n) {
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
    if (rows == cols) {
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

void Matrix::row_swap(int i, int j) {
    if (i >= rows || j >= rows || i < 0 || j < 0) {
        throw astra::internals::exceptions::index_out_of_range();
    }

    for (int k = 0; k < cols; ++k) {
        astra::internals::utils::swap(values[i * cols + k],
                                      values[j * cols + k]);
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

Matrix astra::operator*(const Matrix& mat, double scalar) {
   
    int rows = mat.get_row();
    int cols = mat.get_col();

    Matrix result(rows, cols);

    for (int i = 0; i < rows * cols; ++i) {
        result.values[i] = mat.values[i] * scalar;
    }
    return result;
}

Matrix astra::operator*(double scalar, const Matrix& mat) {
    return mat * scalar; 
}


Matrix astra::operator/(const Matrix& mat, double scalar) {
    if (scalar == 0.0) {
        throw astra::internals::exceptions::zero_division();
    }

    int rows = mat.get_row();
    int cols = mat.get_col();

    Matrix result(rows, cols);

    for (int i = 0; i < rows * cols; ++i) {
        result.values[i] = mat.values[i] / scalar;
    }

    return result;
}

int Matrix::get_row() const { return rows; }
int Matrix::get_col() const { return cols; }

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


std::ostream& astra::operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat.rows; ++i) {
        os << "[";
        for (int j = 0; j < mat.cols; ++j) {
            os << std::setw(8)
               << mat.values[i * mat.cols + j];
            if (j < mat.cols - 1)
                os << ", ";
        }
        os << "]" << std::endl;
    }
    return os;
}
