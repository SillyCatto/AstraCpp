#include "pch.h"
#include "Matrix.h"
#include <stdexcept>

using namespace astra;

Matrix::Matrix(int r, int c)
    : rows(r), cols(c), current_index(0), values(nullptr) {

    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimension must be positive");
    }
    values = new double[r * c];
}

Matrix::~Matrix() { delete[] values; }

Matrix& Matrix::operator<<(double val) {
    if (current_index < (rows * cols)) {
        values[current_index++] = val;
    }
    else {
        throw std::out_of_range("Too many elements for matrix");
    }
    return *this;
}

Matrix &Matrix::operator,(double val) { return (*this << val); }

double& Matrix::operator()(int i, int j) { 
    if (i >= rows || i < 0 || j >= cols || j < 0) {
        throw std::out_of_range("Matrix index out of range");
    }
    return values[i * cols + j];
}

int Matrix::get_row() const { return rows; }
int Matrix::get_col() const { return cols; }
