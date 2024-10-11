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

    Matrix& operator<<(double val);
    Matrix& operator,(double val);
    double& operator()(int i, int j);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;

    int get_row() const;
    int get_col() const;


    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};
} // namespace astra
