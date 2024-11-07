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

    int get_row() const;
    int get_col() const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix& operator=(const Matrix& other);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    void replace(double old_val, double new_val);

    double sum() const;
    double prod() const;
    double principal_prod() const;
    double avg() const;

    double min() const;
    double max() const;

    bool is_square() const;
    bool is_zero() const;

    static Matrix id(int n);

    void transpose();
    void row_swap(int i, int j);

    void clear();

    friend Matrix operator*(const Matrix& mat, double scalar); 
    friend Matrix operator*(double scalar, const Matrix& mat); 
    
    friend Matrix operator/(const Matrix& mat, double scalar);


    void print(int width = 7) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};
} // namespace astra
