#include "pch.h"
#include "Matrix.h"
#include "Exceptions.h"
#include <stdexcept>
#include "Exceptions.h"

using namespace astra;

Matrix::Matrix(int r, int c)
    : rows(r), cols(c), current_index(0), values(nullptr) {

    if (rows <= 0 || cols <= 0) {
        throw astra::internals::exceptions::invalid_size();
    }
    values = new double[r * c];
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

Matrix &Matrix::operator,(double val) { return (*this << val); }

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

int Matrix::get_row() const { return rows; }
int Matrix::get_col() const { return cols; }
