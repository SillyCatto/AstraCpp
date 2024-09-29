#pragma once

namespace astra {
class Matrix {
  private:
    int rows;
    int cols;
    double* values;

  public:
    Matrix(int r, int c);
    ~Matrix();

    int get_row() const;
    int get_col() const;
};
} // namespace astra
