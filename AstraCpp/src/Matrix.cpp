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

double& Matrix::operator()(int i, int j) { return values[i * cols + j]; }

int Matrix::get_row() const { return rows; }
int Matrix::get_col() const { return cols; }
