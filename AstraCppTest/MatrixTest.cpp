#include "pch.h"

#include <iostream>

#include "Matrix.h"
#include "gtest/gtest.h"

#include "Exceptions.h"
#include "MathUtils.h"


namespace astra {

// Test fixture for Matrix class
class MatrixTest : public ::testing::Test {
  protected:
    void SetUp() override {}

    void TearDown() override {}
};


TEST_F(MatrixTest, valid_matrix_creation) {
    Matrix m(2, 3);
    EXPECT_EQ(m.get_row(), 2);
    EXPECT_EQ(m.get_col(), 3);
}


TEST_F(MatrixTest, invalid_matrix_creation) {
    EXPECT_THROW(Matrix(-2, 3), astra::internals::exceptions::invalid_size);
    EXPECT_THROW(Matrix(2, 0), astra::internals::exceptions::invalid_size);
    EXPECT_THROW(Matrix(0, 0), astra::internals::exceptions::invalid_size);
}

TEST_F(MatrixTest, comma_initializer) {
    Matrix m(2, 2);
    m << 1.0, 2.0, 3.0, 4.0;

    EXPECT_EQ(m(0, 0), 1.0);
    EXPECT_EQ(m(0, 1), 2.0);
    EXPECT_EQ(m(1, 0), 3.0);
    EXPECT_EQ(m(1, 1), 4.0);
}

TEST_F(MatrixTest, matrix_addition) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 4; 
    matB << 5 << 6 << 7 << 8; 

    Matrix result = matA + matB;

    EXPECT_EQ(result(0, 0), 6);
    EXPECT_EQ(result(0, 1), 8);
    EXPECT_EQ(result(1, 0), 10);
    EXPECT_EQ(result(1, 1), 12);
}

TEST_F(MatrixTest, matrix_addition_size_mismatch) {
    Matrix matA(2, 2);
    Matrix matB(3, 3);

    matA << 1 << 2 << 3 << 4; 

    EXPECT_THROW(matA + matB, astra::internals::exceptions::matrix_size_mismatch);
}

TEST_F(MatrixTest, matrix_addition_empty) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 4;
    matB << 0 << 0 << 0 << 0; 

    Matrix result = matA + matB;

    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(1, 0), 3);
    EXPECT_EQ(result(1, 1), 4);
}

TEST_F(MatrixTest, matrix_subtraction) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 5 << 6 << 7 << 8; 
    matB << 1 << 2 << 3 << 4; 

    Matrix result = matA - matB;

    EXPECT_EQ(result(0, 0), 4);
    EXPECT_EQ(result(0, 1), 4);
    EXPECT_EQ(result(1, 0), 4);
    EXPECT_EQ(result(1, 1), 4);
}

TEST_F(MatrixTest, matrix_subtraction_size_mismatch) {
    Matrix matA(3, 3);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9; 

    EXPECT_THROW(matA - matB, astra::internals::exceptions::matrix_size_mismatch);
}

TEST_F(MatrixTest, matrix_subtraction_empty) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 4; 
    matB << 0 << 0 << 0 << 0; 

    Matrix result = matA - matB;

    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(1, 0), 3);
    EXPECT_EQ(result(1, 1), 4);
}

TEST_F(MatrixTest, TransposeSquareMatrix) {
    Matrix mat(2, 2, {1.0, 2.0, 3.0, 4.0});
    mat.transpose();

    EXPECT_EQ(mat.get_row(), 2);
    EXPECT_EQ(mat.get_col(), 2);
    EXPECT_EQ(mat(0, 0), 1.0);
    EXPECT_EQ(mat(0, 1), 3.0);
    EXPECT_EQ(mat(1, 0), 2.0);
    EXPECT_EQ(mat(1, 1), 4.0);
}

TEST_F(MatrixTest, TransposeNonSquareMatrixInPlace) {
    Matrix mat(2, 3, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
    mat.transpose();

    EXPECT_EQ(mat.get_row(), 3);
    EXPECT_EQ(mat.get_col(), 2);
    EXPECT_EQ(mat(0, 0), 1.0);
    EXPECT_EQ(mat(0, 1), 4.0);
    EXPECT_EQ(mat(1, 0), 2.0);
    EXPECT_EQ(mat(1, 1), 5.0);
    EXPECT_EQ(mat(2, 0), 3.0);
    EXPECT_EQ(mat(2, 1), 6.0);
}

TEST_F(MatrixTest, scalar_multiplication_matrix_times_scalar) {
    Matrix mat(2, 2);
    mat << 1.0, 2.0, 3.0, 4.0;
    Matrix result = mat * 2.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

TEST_F(MatrixTest, scalar_multiplication_scalar_times_matrix) {
    Matrix mat(2, 2);
    mat << 1.0, 2.0, 3.0, 4.0;
    Matrix result = 3.0 * mat;

    EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 6.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 9.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST_F(MatrixTest, scalar_multiplication_negative_scalar) {
    Matrix mat(2, 2);
    mat << 1.0, -2.0, 3.0, -4.0;
    Matrix result = mat * -1.0;

    EXPECT_DOUBLE_EQ(result(0, 0), -1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), -3.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(MatrixTest, scalar_multiplication_zero_scalar) {
    Matrix mat(2, 2);
    mat << 1.0, 2.0, 3.0, 4.0;
    Matrix result = mat * 0.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

TEST_F(MatrixTest, scalar_multiplication_one_scalar) {
    Matrix mat(2, 2);
    mat << 1.0, 2.0, 3.0, 4.0;
    Matrix result = mat * 1.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(MatrixTest, scalar_division) {
    Matrix mat(2, 2);
    mat << 4.0, 8.0, 12.0, 16.0;

    Matrix result = mat / 4.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(MatrixTest, scalar_division_by_one) {
    Matrix mat(2, 2);
    mat << 3.0, 6.0, 9.0, 12.0;

    Matrix result = mat / 1.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 6.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 9.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST_F(MatrixTest, scalar_division_fraction) {
    Matrix mat(2, 2);
    mat << 2.0, 4.0, 6.0, 8.0;

    Matrix result = mat / 0.5;

    EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 12.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 16.0);
}

TEST_F(MatrixTest, division_by_zero) {
    Matrix mat(2, 2);
    mat << 5.0, 10.0, 15.0, 20.0;

    EXPECT_THROW(mat / 0.0, astra::internals::exceptions::zero_division);
}

TEST_F(MatrixTest, scalar_division_negative_values) {
    Matrix mat(2, 2);
    mat << -10.0, -20.0, 30.0, 40.0;

    Matrix result = mat / 10.0;

    EXPECT_DOUBLE_EQ(result(0, 0), -1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), -2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(MatrixTest, scalar_division_small_result) {
    Matrix mat(2, 2);
    mat << 1e-6, 2e-6, 3e-6, 4e-6;

    Matrix result = mat / 1e6;

    EXPECT_DOUBLE_EQ(result(0, 0), 1e-12);
    EXPECT_DOUBLE_EQ(result(0, 1), 2e-12);
    EXPECT_DOUBLE_EQ(result(1, 0), 3e-12);
    EXPECT_DOUBLE_EQ(result(1, 1), 4e-12);
}

TEST_F(MatrixTest, get_row_test) {
    Matrix mat(2, 3);
    EXPECT_EQ(mat.get_row(), 2);
}

TEST_F(MatrixTest, get_col_test) {
    Matrix mat(2, 3);
    EXPECT_EQ(mat.get_col(), 3);
}

TEST_F(MatrixTest, matrix_assignment_equal) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 4;
    matB = matA;

    EXPECT_EQ(matB(0, 0), 1);
    EXPECT_EQ(matB(0, 1), 2);
    EXPECT_EQ(matB(1, 0), 3);
    EXPECT_EQ(matB(1, 1), 4);
}

TEST_F(MatrixTest, matrix_assignment_different_size) {
    Matrix matA(2, 2);
    Matrix matB(3, 3);

    matA << 1 << 2 << 3 << 4;

    matB = matA;

    EXPECT_EQ(matB(0, 0), 1);
    EXPECT_EQ(matB(0, 1), 2);
    EXPECT_EQ(matB(1, 0), 3);
    EXPECT_EQ(matB(1, 1), 4);
}

TEST_F(MatrixTest, matrix_equality) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 4;
    matB << 1 << 2 << 3 << 4;

    EXPECT_TRUE(matA == matB);
}

TEST_F(MatrixTest, matrix_inequality) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 6;
    matB << 1 << 2 << 3 << 4;

    EXPECT_FALSE(matA == matB);
}

TEST_F(MatrixTest, matrix_replace) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;

    mat.replace(2, 5);

    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 5);
    EXPECT_EQ(mat(1, 0), 3);
    EXPECT_EQ(mat(1, 1), 4);
}

TEST_F(MatrixTest, matrix_replace_all) { 
    Matrix mat(2, 2);
    mat << 4 << 4 << 4 << 4;
    
    mat.replace(4, 9);

    EXPECT_EQ(mat(0, 0), 9);
    EXPECT_EQ(mat(0, 1), 9);
    EXPECT_EQ(mat(1, 0), 9);
    EXPECT_EQ(mat(1, 1), 9);
}

TEST_F(MatrixTest, matrix_sum_positive) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.sum(), 10);
}


} // namespace astra