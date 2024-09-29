#include "pch.h"
#include "Matrix.h"

using namespace astra;

Matrix::Matrix(int r, int c) : rows(r), cols(c) { values = new double[r * c]; }

Matrix::~Matrix() { delete[] values; }

int Matrix::get_row() const { return rows; }
int Matrix::get_col() const { return cols; }
