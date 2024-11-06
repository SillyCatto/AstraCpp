#pragma once
#include <iostream>

namespace astra {
class Matrix {
  private:
    int rows;
    int cols;
    int current_index;
    double* values;

  public:
    Matrix(int r, int c);
    Matrix(int r, int c, const double values[]);
    Matrix(int r, int c, std::initializer_list<double> values);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator<<(double val);
    Matrix& operator,(double val);
    double& operator()(int i, int j);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix& operator=(const Matrix& other);
    bool operator==(const Matrix& other) const;

    void replace(double old_val, double new_val);
    bool is_square() const;

    static Matrix id(int n);

    friend Matrix operator*(const Matrix& mat, double scalar); 
    friend Matrix operator*(double scalar, const Matrix& mat); 
    
    friend Matrix operator/(const Matrix& mat, double scalar);

    int get_row() const;
    int get_col() const;

    void print(int width = 7) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};
} // namespace astra
