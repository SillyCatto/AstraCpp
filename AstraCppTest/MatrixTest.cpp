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
    EXPECT_EQ(m.num_row(), 2);
    EXPECT_EQ(m.num_col(), 3);
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

TEST_F(MatrixTest, InsertValidValue) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(1, 1), 4);
}

TEST_F(MatrixTest, InsertExceedingMatrixSize) {
    Matrix mat(2, 2);
    EXPECT_THROW(mat << 1 << 2 << 3 << 4 << 5,
                 astra::internals::exceptions::init_out_of_range);
}

TEST_F(MatrixTest, InsertPartialFill) {
    Matrix mat(2, 2);
    mat << 1 << 2;
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(1, 0), 0);
    EXPECT_EQ(mat(1, 1), 0); 
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

TEST_F(MatrixTest, matrix_multiplication) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 4;
    matB << 5 << 6 << 7 << 8;

    Matrix result = matA * matB;

    EXPECT_EQ(result(0, 0), 19);
    EXPECT_EQ(result(0, 1), 22);
    EXPECT_EQ(result(1, 0), 43);
    EXPECT_EQ(result(1, 1), 50);
}

TEST_F(MatrixTest, matrix_multiplication_size_mismatch) {
    Matrix matA(2, 2);
    Matrix matB(3, 3);

    matA << 1 << 2 << 3 << 4;

    EXPECT_THROW(
        matA * matB,
        astra::internals::exceptions::matrix_multiplication_size_mismatch);
}

TEST_F(MatrixTest, matrix_multiplication_empty) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 4;
    matB << 0 << 0 << 0 << 0;

    Matrix result = matA * matB;

    EXPECT_EQ(result(0, 0), 0);
    EXPECT_EQ(result(0, 1), 0);
    EXPECT_EQ(result(1, 0), 0);
    EXPECT_EQ(result(1, 1), 0);
}

TEST_F(MatrixTest, matrix_multiplication_identity) {
    Matrix matA(2, 2);
    Matrix matB = Matrix::identity(2);

    matA << 1 << 2 << 3 << 4;

    Matrix result = matA * matB;

    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(1, 0), 3);
    EXPECT_EQ(result(1, 1), 4);
}

TEST_F(MatrixTest, matrix_multiplication_identity_reverse) {
    Matrix matA(2, 2);
    Matrix matB = Matrix::identity(2);

    matA << 1 << 2 << 3 << 4;

    Matrix result = matB * matA;

    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(1, 0), 3);
    EXPECT_EQ(result(1, 1), 4);
}

TEST_F(MatrixTest, transpose_square_matrix_in_place) {
    Matrix mat(2, 2, {1.0, 2.0, 3.0, 4.0});
    mat.transpose();

    EXPECT_EQ(mat.num_row(), 2);
    EXPECT_EQ(mat.num_col(), 2);
    EXPECT_EQ(mat(0, 0), 1.0);
    EXPECT_EQ(mat(0, 1), 3.0);
    EXPECT_EQ(mat(1, 0), 2.0);
    EXPECT_EQ(mat(1, 1), 4.0);
}

TEST_F(MatrixTest, transpose_nonsquare_matrix_in_place) {
    Matrix mat(2, 3, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
    mat.transpose();

    EXPECT_EQ(mat.num_row(), 3);
    EXPECT_EQ(mat.num_col(), 2);
    EXPECT_EQ(mat(0, 0), 1.0);
    EXPECT_EQ(mat(0, 1), 4.0);
    EXPECT_EQ(mat(1, 0), 2.0);
    EXPECT_EQ(mat(1, 1), 5.0);
    EXPECT_EQ(mat(2, 0), 3.0);
    EXPECT_EQ(mat(2, 1), 6.0);
}

TEST_F(MatrixTest, transpose_single_row_matrix) {
    Matrix mat(1, 3, {1.0, 2.0, 3.0});
    mat.transpose();

    EXPECT_EQ(mat.num_row(), 3);
    EXPECT_EQ(mat.num_col(), 1);
    EXPECT_EQ(mat(0, 0), 1.0);
    EXPECT_EQ(mat(1, 0), 2.0);
    EXPECT_EQ(mat(2, 0), 3.0);
}

TEST_F(MatrixTest, transpose_single_column_matrix) {
    Matrix mat(3, 1, {1.0, 2.0, 3.0});
    mat.transpose();

    EXPECT_EQ(mat.num_row(), 1);
    EXPECT_EQ(mat.num_col(), 3);
    EXPECT_EQ(mat(0, 0), 1.0);
    EXPECT_EQ(mat(0, 1), 2.0);
    EXPECT_EQ(mat(0, 2), 3.0);
}

TEST_F(MatrixTest, transpose_already_transposed_matrix) {
    Matrix mat(2, 3, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
    mat.transpose();
    mat.transpose(); // again transpose

    EXPECT_EQ(mat.num_row(), 2);
    EXPECT_EQ(mat.num_col(), 3);
    EXPECT_EQ(mat(0, 0), 1.0);
    EXPECT_EQ(mat(0, 1), 2.0);
    EXPECT_EQ(mat(0, 2), 3.0);
    EXPECT_EQ(mat(1, 0), 4.0);
    EXPECT_EQ(mat(1, 1), 5.0);
    EXPECT_EQ(mat(1, 2), 6.0);
}

TEST_F(MatrixTest, row_swap_square) { 
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;

    mat.row_swap(0, 1);

    EXPECT_EQ(mat(0, 0), 3);
    EXPECT_EQ(mat(0, 1), 4);
    EXPECT_EQ(mat(1, 0), 1);
    EXPECT_EQ(mat(1, 1), 2);
}

TEST_F(MatrixTest, row_swap_not_square) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 << 4 << 5 << 6;

    mat.row_swap(0, 1);

    EXPECT_EQ(mat(0, 0), 4);
    EXPECT_EQ(mat(0, 1), 5);
    EXPECT_EQ(mat(0, 2), 6);
    EXPECT_EQ(mat(1, 0), 1);
    EXPECT_EQ(mat(1, 1), 2);
    EXPECT_EQ(mat(1, 2), 3);
    
}

TEST_F(MatrixTest, row_swap_not_square_test) {
    Matrix mat(3, 2);
    mat << 1 << 2 << 3 << 4 << 5 << 6;

    mat.row_swap(0, 1);

    EXPECT_EQ(mat(0, 0), 3);
    EXPECT_EQ(mat(0, 1), 4);
    EXPECT_EQ(mat(1, 0), 1);
    EXPECT_EQ(mat(1, 1), 2);
    EXPECT_EQ(mat(2, 0), 5);
    EXPECT_EQ(mat(2, 1), 6);
}
TEST_F(MatrixTest, row_swap_not_square_greater) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 << 4 << 5 << 6;

    EXPECT_THROW(mat.row_swap(2, 1),
                 astra::internals::exceptions::index_out_of_range);

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
    EXPECT_EQ(mat.num_row(), 2);
}

TEST_F(MatrixTest, get_col_test) {
    Matrix mat(2, 3);
    EXPECT_EQ(mat.num_col(), 3);
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

TEST_F(MatrixTest, matrix_equality_false) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 6;
    matB << 1 << 2 << 3 << 4;

    EXPECT_FALSE(matA == matB);
}

TEST_F(MatrixTest, matrix_equality_diff_size) {
    Matrix matA(2, 3);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 6 << 5 << 7;
    matB << 1 << 2 << 3 << 4;

    EXPECT_FALSE(matA == matB);
}

TEST_F(MatrixTest, matrix_inequality_true) {
    Matrix matA(2, 3);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 6 << 5 << 7;
    matB << 1 << 2 << 3 << 4;

    EXPECT_TRUE(matA != matB);
}

TEST_F(MatrixTest, matrix_inequality_false) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 4;
    matB << 1 << 2 << 3 << 4;

    EXPECT_FALSE(matA != matB);
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

TEST_F(MatrixTest, ReplaceNonexistentValue) {
    Matrix mat(2, 2, {1, 2, 3, 4});
    mat.replace(99, 8);

    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(1, 0), 3);
    EXPECT_EQ(mat(1, 1), 4);
}

TEST_F(MatrixTest, matrix_sum_positive) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.sum(), 10);
}

TEST_F(MatrixTest, matrix_sum_negative) {
    Matrix mat(2, 2);
    mat << -1 << -2 << -3 << -4;

    EXPECT_DOUBLE_EQ(mat.sum(), -10);
}

TEST_F(MatrixTest, matrix_sum_zero) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << -6;

    EXPECT_DOUBLE_EQ(mat.sum(), 0);
}

TEST_F(MatrixTest, matrix_sum_large) {
    Matrix mat(2, 2);
    mat << 1e6 << 2e6 << 3e6 << 4e6;

    EXPECT_DOUBLE_EQ(mat.sum(), 10e6);
}

TEST_F(MatrixTest, matrix_prod_positive) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.prod(), 24);
}

TEST_F(MatrixTest, matrix_prod_negative) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << -4;

    EXPECT_DOUBLE_EQ(mat.prod(), -24);
}

TEST_F(MatrixTest, matrix_prod_zero) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 0;

    EXPECT_DOUBLE_EQ(mat.prod(), 0);
}

TEST_F(MatrixTest, matrix_prod_large) {
    Matrix mat(2, 2);
    mat << 1e6 << 2e6 << 3e6 << 4e6;

    EXPECT_DOUBLE_EQ(mat.prod(), 24e24);
}

TEST_F(MatrixTest, matrix_trace_square) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.trace(), 5);
}

TEST_F(MatrixTest, matrix_trace_non_square) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 << 4 << 5 << 6;

    EXPECT_THROW(mat.trace(),
                 astra::internals::exceptions::invalid_argument);
}

TEST_F(MatrixTest, matrix_trace_singleton) { 
    Matrix mat(1, 1); 
    mat << 5;

    EXPECT_DOUBLE_EQ(mat.trace(), 5);
}

TEST_F(MatrixTest, matrix_avg_positive) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.avg(), 2.5);
}

TEST_F(MatrixTest, matrix_avg_negative) {
    Matrix mat(2, 2);
    mat << -1 << -2 << -3 << -4;

    EXPECT_DOUBLE_EQ(mat.avg(), -2.5);
}

TEST_F(MatrixTest, matrix_avg_zero) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << -6;

    EXPECT_DOUBLE_EQ(mat.avg(), 0);
}

TEST_F(MatrixTest, matrix_avg_singleton) {
    Matrix mat(1, 1);
    mat << -6;

    EXPECT_DOUBLE_EQ(mat.avg(), -6);
}

TEST_F(MatrixTest, matrix_min_singleton) {
    Matrix mat(1, 1);
    mat << -6;

    EXPECT_DOUBLE_EQ(mat.min(), -6);
}

TEST_F(MatrixTest, matrix_min_zero) {
    Matrix mat(2, 2);
    mat << 1 << 0 << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.min(), 0);
}

TEST_F(MatrixTest, matrix_min_same) {
    Matrix mat(2, 2);
    mat << 1 << 1 << 1 << 1;

    EXPECT_DOUBLE_EQ(mat.min(), 1);
}

TEST_F(MatrixTest, matrix_max_same) {
    Matrix mat(2, 2);
    mat << 1 << 1 << 1 << 1;

    EXPECT_DOUBLE_EQ(mat.max(), 1);
}

TEST_F(MatrixTest, matrix_max_singleton) {
    Matrix mat(1, 1);
    mat << -6;

    EXPECT_DOUBLE_EQ(mat.max(), -6);
}

TEST_F(MatrixTest, matrix_max_zero) {
    Matrix mat(2, 2);
    mat << -10 << 0 << -45 << -1;

    EXPECT_DOUBLE_EQ(mat.max(), 0);
}

TEST_F(MatrixTest, matrix_max_positive) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.max(), 4);
}

TEST_F(MatrixTest, matrix_max_negative) {
    Matrix mat(2, 2);
    mat << -1 << -2 << -3 << -4;

    EXPECT_DOUBLE_EQ(mat.max(), -1);
}

TEST_F(MatrixTest, is_square_true) {
    Matrix mat(2, 2);
    EXPECT_TRUE(mat.is_square());
}

TEST_F(MatrixTest, is_square_false) {
    Matrix mat(2, 1);
    EXPECT_FALSE(mat.is_square());
}

TEST_F(MatrixTest, is_rectangular_true) { 
    Matrix mat(2, 1);
    EXPECT_TRUE(mat.is_rectangular());
}

TEST_F(MatrixTest, is_rectangular_false) {
    Matrix mat(2, 2);
    EXPECT_FALSE(mat.is_rectangular());
}

TEST_F(MatrixTest, is_identity_true) {
    Matrix mat = Matrix::identity(3);
    EXPECT_TRUE(mat.is_identity());

}

TEST_F(MatrixTest, is_identity_false) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;
    EXPECT_FALSE(mat.is_identity());
}

TEST_F(MatrixTest, is_identity_non1) { 
    Matrix mat(2, 2); 
    mat << 2 << 0 << 0 << 2;
    EXPECT_FALSE(mat.is_identity());
}

TEST_F(MatrixTest, is_symmetric_true) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 2 << 5;
    EXPECT_TRUE(mat.is_symmetric());
}

TEST_F(MatrixTest, is_symmetric_false) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;
    EXPECT_FALSE(mat.is_symmetric());
}

TEST_F(MatrixTest, TrueDiagonalMatrix) {
    Matrix diag_matrix(3, 3, {1, 0, 0, 0, 2, 0, 0, 0, 3});
    EXPECT_TRUE(diag_matrix.is_diagonal());
}

TEST_F(MatrixTest, FalseDiagonalMatrix) {
    Matrix non_diag_matrix(3, 3, {1, 2, 0, 0, 2, 0, 0, 1, 3});
    EXPECT_FALSE(non_diag_matrix.is_diagonal());
}

TEST_F(MatrixTest, SingleElementMatrix) {
    Matrix single_element_matrix(1, 1, {5});
    EXPECT_TRUE(single_element_matrix.is_diagonal());
}

TEST_F(MatrixTest, NonSquareMatrix) {
    Matrix non_square_matrix(2, 3, {1, 0, 0, 0, 2, 0});
    EXPECT_FALSE(non_square_matrix.is_diagonal());
}

TEST_F(MatrixTest, TrueUpperTriangularMatrix) {
    Matrix upper_triangular_matrix(3, 3, {1, 2, 3, 0, 5, 6, 0, 0, 9});
    EXPECT_TRUE(upper_triangular_matrix.is_upper_triangular());
}

TEST_F(MatrixTest, ZeroUpperTriangularMatrix) {
    Matrix zero_upper_triangular_matrix(3, 3, {0, 2, 3, 0, 0, 6, 0, 0, 0});
    EXPECT_TRUE(zero_upper_triangular_matrix.is_upper_triangular());
}

TEST_F(MatrixTest, UpperTriangularWithZeroOnDiagonal) {
    Matrix zero_diag_upper_triangular_matrix(3, 3, {1, 2, 3, 0, 0, 6, 0, 0, 9});
    EXPECT_TRUE(zero_diag_upper_triangular_matrix.is_upper_triangular());
}

TEST_F(MatrixTest, TrueLowerTriangularMatrix) {
    Matrix lower_triangular_matrix(3, 3, {1, 0, 0, 4, 5, 0, 7, 8, 9});
    EXPECT_TRUE(lower_triangular_matrix.is_lower_triangular());
}

TEST_F(MatrixTest, ZeroLowerTriangularMatrix) {
    Matrix zero_lower_triangular_matrix(3, 3, {0, 0, 0, 4, 0, 0, 7, 8, 0});
    EXPECT_TRUE(zero_lower_triangular_matrix.is_lower_triangular());
}

TEST_F(MatrixTest, LowerTriangularWithZeroOnDiagonal) {
    Matrix zero_diag_lower_triangular_matrix(3, 3, {1, 0, 0, 4, 0, 0, 7, 8, 0});
    EXPECT_TRUE(zero_diag_lower_triangular_matrix.is_lower_triangular());
}

TEST_F(MatrixTest, IdentityMatrixIsTriangular) {
    Matrix identity_matrix(3, 3, {1, 0, 0, 0, 1, 0, 0, 0, 1});
    EXPECT_TRUE(identity_matrix.is_triangular());
    EXPECT_TRUE(identity_matrix.is_upper_triangular());
    EXPECT_TRUE(identity_matrix.is_lower_triangular());
    EXPECT_TRUE(identity_matrix.is_diagonal());
}

TEST_F(MatrixTest, ZeroMatrixIsTriangularAndDiagonal) {
    Matrix zero_matrix(3, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0});
    EXPECT_TRUE(zero_matrix.is_triangular());
    EXPECT_TRUE(zero_matrix.is_diagonal());
}

TEST_F(MatrixTest, is_zero_true) {
    Matrix mat(2, 2);
    EXPECT_TRUE(mat.is_zero());
}

TEST_F(MatrixTest, is_zero_false) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;
    EXPECT_FALSE(mat.is_zero());
}

TEST_F(MatrixTest, identity_pos) { 
    Matrix mat = Matrix::identity(3); 

    EXPECT_DOUBLE_EQ(mat(0, 0), 1);
    EXPECT_DOUBLE_EQ(mat(0, 1), 0);
    EXPECT_DOUBLE_EQ(mat(0, 2), 0);
    EXPECT_DOUBLE_EQ(mat(1, 0), 0);
    EXPECT_DOUBLE_EQ(mat(1, 1), 1);
    EXPECT_DOUBLE_EQ(mat(1, 2), 0);
    EXPECT_DOUBLE_EQ(mat(2, 0), 0);
    EXPECT_DOUBLE_EQ(mat(2, 1), 0);
    EXPECT_DOUBLE_EQ(mat(2, 2), 1);

}

TEST_F(MatrixTest, identity_zero) {
    EXPECT_THROW(Matrix::identity(0),
                 astra::internals::exceptions::invalid_size);
}

TEST_F(MatrixTest, clear) { 
    Matrix mat(2, 2); 
    mat << 1 << 2 << 3 << 4;

    mat.clear();

    EXPECT_DOUBLE_EQ(mat(0, 0), 0);
    EXPECT_DOUBLE_EQ(mat(0, 1), 0);
    EXPECT_DOUBLE_EQ(mat(1, 0), 0);
    EXPECT_DOUBLE_EQ(mat(1, 1), 0);
}

TEST_F(MatrixTest, fill) {
    Matrix mat(2, 2);
    mat.fill(2);

    EXPECT_DOUBLE_EQ(mat(0, 0), 2);
    EXPECT_DOUBLE_EQ(mat(0, 1), 2);
    EXPECT_DOUBLE_EQ(mat(1, 0), 2);
    EXPECT_DOUBLE_EQ(mat(1, 1), 2);
}

TEST_F(MatrixTest, resize_invalid) { 
    Matrix mat(2, 2);
    EXPECT_THROW(mat.resize(0, 2), astra::internals::exceptions::invalid_size);
}

TEST_F(MatrixTest, resize_larger) {
    Matrix mat(2, 2);
    mat.resize(3, 3);

    EXPECT_DOUBLE_EQ(mat(0, 0), 0);
    EXPECT_DOUBLE_EQ(mat(0, 1), 0);
    EXPECT_DOUBLE_EQ(mat(0, 2), 0);
    EXPECT_DOUBLE_EQ(mat(1, 0), 0);
    EXPECT_DOUBLE_EQ(mat(1, 1), 0);
    EXPECT_DOUBLE_EQ(mat(1, 2), 0);
    EXPECT_DOUBLE_EQ(mat(2, 0), 0);
    EXPECT_DOUBLE_EQ(mat(2, 1), 0);
    EXPECT_DOUBLE_EQ(mat(2, 2), 0);
}

TEST_F(MatrixTest, resize_smaller) {
    Matrix mat(3, 3);
    mat.resize(2, 2);

    EXPECT_DOUBLE_EQ(mat(0, 0), 0);
    EXPECT_DOUBLE_EQ(mat(0, 1), 0);
    EXPECT_DOUBLE_EQ(mat(1, 0), 0);
    EXPECT_DOUBLE_EQ(mat(1, 1), 0);
}

TEST_F(MatrixTest, matrix_join_same_rows) {
    Matrix matA = Matrix(2, 2, {1.0, 2.0, 3.0, 4.0});
    Matrix matB = Matrix(2, 3, {5.0, 6.0, 7.0, 8.0, 9.0, 10.0});

    matA.join(matB);

    EXPECT_EQ(matA.num_row(), 2);
    EXPECT_EQ(matA.num_col(), 5);

    EXPECT_DOUBLE_EQ(matA(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(matA(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(matA(0, 2), 5.0);
    EXPECT_DOUBLE_EQ(matA(0, 3), 6.0);
    EXPECT_DOUBLE_EQ(matA(0, 4), 7.0);

    EXPECT_DOUBLE_EQ(matA(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(matA(1, 1), 4.0);
    EXPECT_DOUBLE_EQ(matA(1, 2), 8.0);
    EXPECT_DOUBLE_EQ(matA(1, 3), 9.0);
    EXPECT_DOUBLE_EQ(matA(1, 4), 10.0);
}

TEST_F(MatrixTest, matrix_join_mismatched_rows) {
    Matrix matA = Matrix(2, 2, {1.0, 2.0, 3.0, 4.0});
    Matrix matB = Matrix(3, 2, {5.0, 6.0, 7.0, 8.0, 9.0, 10.0});

    EXPECT_THROW(matA.join(matB),
                 astra::internals::exceptions::matrix_join_size_mismatch);
}

TEST_F(MatrixTest, matrix_join_single_row_matrices) {
    Matrix matA = Matrix(1, 2, {1.0, 2.0});
    Matrix matB = Matrix(1, 3, {3.0, 4.0, 5.0});

    matA.join(matB);

    EXPECT_EQ(matA.num_row(), 1);
    EXPECT_EQ(matA.num_col(), 5);

    EXPECT_DOUBLE_EQ(matA(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(matA(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(matA(0, 2), 3.0);
    EXPECT_DOUBLE_EQ(matA(0, 3), 4.0);
    EXPECT_DOUBLE_EQ(matA(0, 4), 5.0);
}

TEST_F(MatrixTest, matrix_join_single_column_matrices) {
    Matrix matA = Matrix(3, 1, {1.0, 2.0, 3.0});
    Matrix matB = Matrix(3, 2, {4.0, 5.0, 6.0, 7.0, 8.0, 9.0});

    matA.join(matB);

    EXPECT_EQ(matA.num_row(), 3);
    EXPECT_EQ(matA.num_col(), 3);

    EXPECT_DOUBLE_EQ(matA(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(matA(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(matA(0, 2), 5.0);

    EXPECT_DOUBLE_EQ(matA(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(matA(1, 1), 6.0);
    EXPECT_DOUBLE_EQ(matA(1, 2), 7.0);

    EXPECT_DOUBLE_EQ(matA(2, 0), 3.0);
    EXPECT_DOUBLE_EQ(matA(2, 1), 8.0);
    EXPECT_DOUBLE_EQ(matA(2, 2), 9.0);
}

TEST_F(MatrixTest, matrix_join_large_matrices) {
    double valuesA[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Matrix matA(4, 4, valuesA);

    double valuesB[] = {17, 18, 19, 20, 21, 22, 23, 24};
    Matrix matB(4, 2, valuesB);

    matA.join(matB);

    EXPECT_EQ(matA.num_row(), 4);
    EXPECT_EQ(matA.num_col(), 6);

    EXPECT_DOUBLE_EQ(matA(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(matA(0, 4), 17.0);
    EXPECT_DOUBLE_EQ(matA(3, 5), 24.0);
}

TEST_F(MatrixTest, matrix_join_with_empty_other_matrix) {
    Matrix matA = Matrix(2, 2, {1.0, 2.0, 3.0, 4.0});
    Matrix matB = Matrix(2, 1);

    matA.join(matB);

    EXPECT_EQ(matA.num_row(), 2);
    EXPECT_EQ(matA.num_col(), 3);

    EXPECT_DOUBLE_EQ(matA(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(matA(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(matA(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(matA(1, 1), 4.0);
}

TEST_F(MatrixTest, matrix_join_both_empty_matrices) {
    Matrix matA = Matrix(2, 2); 
    Matrix matB = Matrix(2, 3); 

    matA.join(matB);

    EXPECT_EQ(matA.num_row(), 2);
    EXPECT_EQ(matA.num_col(), 5);
}

TEST_F(MatrixTest, matrix_join_with_negative_values) {
    Matrix matA = Matrix(2, 2, {-1.0, -2.0, -3.0, -4.0});
    Matrix matB = Matrix(2, 2, {5.0, -6.0, 7.0, -8.0});

    matA.join(matB);

    EXPECT_EQ(matA.num_row(), 2);
    EXPECT_EQ(matA.num_col(), 4);

    EXPECT_DOUBLE_EQ(matA(0, 0), -1.0);
    EXPECT_DOUBLE_EQ(matA(0, 1), -2.0);
    EXPECT_DOUBLE_EQ(matA(0, 2), 5.0);
    EXPECT_DOUBLE_EQ(matA(0, 3), -6.0);

    EXPECT_DOUBLE_EQ(matA(1, 0), -3.0);
    EXPECT_DOUBLE_EQ(matA(1, 1), -4.0);
    EXPECT_DOUBLE_EQ(matA(1, 2), 7.0);
    EXPECT_DOUBLE_EQ(matA(1, 3), -8.0);
}

TEST_F(MatrixTest, ValidSubmatrix) {
    Matrix mat(4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});

    Matrix submat = mat.submatrix(1, 1, 2, 2);
    Matrix expected(2, 2, {6, 7, 10, 11});

    EXPECT_EQ(submat, expected);
}

TEST_F(MatrixTest, SingleRowSubmatrix) {
    Matrix mat(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

    Matrix submat = mat.submatrix(1, 0, 1, 2);
    Matrix expected(1, 3, {4, 5, 6});

    EXPECT_EQ(submat, expected);
}

TEST_F(MatrixTest, SingleColumnSubmatrix) {
    Matrix mat(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

    Matrix submat = mat.submatrix(0, 1, 2, 1);
    Matrix expected(3, 1, {2, 5, 8});

    EXPECT_EQ(submat, expected);
}

TEST_F(MatrixTest, OneByOneSubmatrix) {
    Matrix mat(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

    Matrix submat = mat.submatrix(1, 1, 1, 1);
    Matrix expected(1, 1, {5});

    EXPECT_EQ(submat, expected);
}

TEST_F(MatrixTest, OutOfBoundsSubmatrix) {
    Matrix mat(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

    EXPECT_THROW(mat.submatrix(-1, 0, 1, 1), astra::internals::exceptions::index_out_of_range);
    EXPECT_THROW(mat.submatrix(0, 0, 3, 3), astra::internals::exceptions::index_out_of_range);
}

} // namespace astra