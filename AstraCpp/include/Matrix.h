#pragma once

namespace astra {
class Matrix {
  private:
    int rows;
    int cols;
    int current_index;
    double* values;

  public:
    Matrix(int r, int c);
    ~Matrix();

    double& operator()(int i, int j);

    int get_row() const;
    int get_col() const;
};
} // namespace astra
