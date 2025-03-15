#include "pch.h"

#include <iostream>

#include "Matrix.h"
#include "Vector.h" 
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
    m << 1.0, 2.0, 
         3.0, 4.0;

    EXPECT_EQ(m(0, 0), 1.0);
    EXPECT_EQ(m(0, 1), 2.0);
    EXPECT_EQ(m(1, 0), 3.0);
    EXPECT_EQ(m(1, 1), 4.0);
}

TEST_F(MatrixTest, insert_valid_value) {
    Matrix mat(2, 2);
    mat << 1 << 2 << 3 << 4;
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(1, 1), 4);
}

TEST_F(MatrixTest, insert_exceeding_matrix_size) {
    Matrix mat(2, 2);
    EXPECT_THROW(mat << 1 << 2 << 3 << 4 << 5,
                 astra::internals::exceptions::init_out_of_range);
}

TEST_F(MatrixTest, insert_partial_fill) {
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

    matA << 1 << 2 
         << 3 << 4; 

    matB << 5 << 6 
         << 7 << 8; 

    Matrix result = matA + matB;

    EXPECT_EQ(result(0, 0), 6);
    EXPECT_EQ(result(0, 1), 8);
    EXPECT_EQ(result(1, 0), 10);
    EXPECT_EQ(result(1, 1), 12);
}

TEST_F(MatrixTest, matrix_addition_size_mismatch) {
    Matrix matA(2, 2);
    Matrix matB(3, 3);

    matA << 1 << 2 
         << 3 << 4; 

    EXPECT_THROW(matA + matB, astra::internals::exceptions::matrix_size_mismatch);
}

TEST_F(MatrixTest, matrix_addition_empty) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 
         << 3 << 4;

    matB << 0 << 0 
         << 0 << 0; 

    Matrix result = matA + matB;

    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(1, 0), 3);
    EXPECT_EQ(result(1, 1), 4);
}

TEST_F(MatrixTest, matrix_subtraction) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 5 << 6 
         << 7 << 8; 

    matB << 1 << 2 
         << 3 << 4; 

    Matrix result = matA - matB;

    EXPECT_EQ(result(0, 0), 4);
    EXPECT_EQ(result(0, 1), 4);
    EXPECT_EQ(result(1, 0), 4);
    EXPECT_EQ(result(1, 1), 4);
}

TEST_F(MatrixTest, matrix_subtraction_size_mismatch) {
    Matrix matA(3, 3);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 
         << 4 << 5 << 6 
         << 7 << 8 << 9; 

    EXPECT_THROW(matA - matB, astra::internals::exceptions::matrix_size_mismatch);
}

TEST_F(MatrixTest, matrix_subtraction_empty) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 
         << 3 << 4; 

    matB << 0 << 0 
         << 0 << 0; 

    Matrix result = matA - matB;

    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(1, 0), 3);
    EXPECT_EQ(result(1, 1), 4);
}

TEST_F(MatrixTest, matrix_multiplication) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 
         << 3 << 4;
    matB << 5 << 6 
         << 7 << 8;

    Matrix result = matA * matB;

    EXPECT_EQ(result(0, 0), 19);
    EXPECT_EQ(result(0, 1), 22);
    EXPECT_EQ(result(1, 0), 43);
    EXPECT_EQ(result(1, 1), 50);
}

TEST_F(MatrixTest, matrix_multiplication_size_mismatch) {
    Matrix matA(2, 2);
    Matrix matB(3, 3);

    matA << 1 << 2 
         << 3 << 4;

    EXPECT_THROW(
        matA * matB,
        astra::internals::exceptions::matrix_multiplication_size_mismatch);
}

TEST_F(MatrixTest, matrix_multiplication_empty) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 
         << 3 << 4;

    matB << 0 << 0 
         << 0 << 0;

    Matrix result = matA * matB;

    EXPECT_EQ(result(0, 0), 0);
    EXPECT_EQ(result(0, 1), 0);
    EXPECT_EQ(result(1, 0), 0);
    EXPECT_EQ(result(1, 1), 0);
}

TEST_F(MatrixTest, matrix_multiplication_identity) {
    Matrix matA(2, 2);
    Matrix matB = Matrix::identity(2);

    matA << 1 << 2 
         << 3 << 4;

    Matrix result = matA * matB;

    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(1, 0), 3);
    EXPECT_EQ(result(1, 1), 4);
}

TEST_F(MatrixTest, matrix_multiplication_identity_reverse) {
    Matrix matA(2, 2);
    Matrix matB = Matrix::identity(2);

    matA << 1 << 2 
         << 3 << 4;

    Matrix result = matB * matA;

    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(1, 0), 3);
    EXPECT_EQ(result(1, 1), 4);
}

TEST_F(MatrixTest, transpose_square_matrix_in_place) {
    Matrix mat(2, 2, {1.0, 2.0, 
                      3.0, 4.0});
    mat.transpose();

    EXPECT_EQ(mat.num_row(), 2);
    EXPECT_EQ(mat.num_col(), 2);
    EXPECT_EQ(mat(0, 0), 1.0);
    EXPECT_EQ(mat(0, 1), 3.0);
    EXPECT_EQ(mat(1, 0), 2.0);
    EXPECT_EQ(mat(1, 1), 4.0);
}

TEST_F(MatrixTest, transpose_nonsquare_matrix_in_place) {
    Matrix mat(2, 3, {1.0, 2.0, 3.0, 
                      4.0, 5.0, 6.0});
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
    Matrix mat(3, 1, {1.0, 
                      2.0, 
                      3.0});
    mat.transpose();

    EXPECT_EQ(mat.num_row(), 1);
    EXPECT_EQ(mat.num_col(), 3);
    EXPECT_EQ(mat(0, 0), 1.0);
    EXPECT_EQ(mat(0, 1), 2.0);
    EXPECT_EQ(mat(0, 2), 3.0);
}

TEST_F(MatrixTest, transpose_already_transposed_matrix) {
    Matrix mat(2, 3, {1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0});
    mat.transpose();
    mat.transpose();

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
    mat << 1 << 2 
        << 3 << 4;

    mat.row_swap(0, 1);

    EXPECT_EQ(mat(0, 0), 3);
    EXPECT_EQ(mat(0, 1), 4);
    EXPECT_EQ(mat(1, 0), 1);
    EXPECT_EQ(mat(1, 1), 2);
}

TEST_F(MatrixTest, row_swap_not_square) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 
        << 4 << 5 << 6;

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
    mat << 1 << 2 
        << 3 << 4 
        << 5 << 6;

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
    mat << 1 << 2 << 3 
        << 4 << 5 << 6;

    EXPECT_THROW(mat.row_swap(2, 1),
                 astra::internals::exceptions::index_out_of_range);

}

TEST_F(MatrixTest, partial_row_swap_square) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << 4;

    mat.partial_row_swap(0, 1, 1);

    EXPECT_EQ(mat(0, 0), 3);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(1, 0), 1);
    EXPECT_EQ(mat(1, 1), 4);
}

TEST_F(MatrixTest, partial_row_swap_not_square) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 
        << 4 << 5 << 6;

    mat.partial_row_swap(0, 1, 2);

    EXPECT_EQ(mat(0, 0), 4);
    EXPECT_EQ(mat(0, 1), 5);
    EXPECT_EQ(mat(0, 2), 3);
    EXPECT_EQ(mat(1, 0), 1);
    EXPECT_EQ(mat(1, 1), 2);
    EXPECT_EQ(mat(1, 2), 6);
}

TEST_F(MatrixTest, partial_row_swap_not_square_greater) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 
        << 4 << 5 << 6;

    EXPECT_THROW(mat.partial_row_swap(2, 1, 1),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, partial_row_swap_not_square_smaller) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 
        << 4 << 5 << 6;

    EXPECT_THROW(mat.partial_row_swap(0, 1, 4),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, col_swap_square) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << 4;

    mat.col_swap(0, 1);

    EXPECT_EQ(mat(0, 0), 2);
    EXPECT_EQ(mat(0, 1), 1);
    EXPECT_EQ(mat(1, 0), 4);
    EXPECT_EQ(mat(1, 1), 3);
    
}

TEST_F(MatrixTest, col_swap_not_square) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 
        << 4 << 5 << 6;

    mat.col_swap(0, 1);

    EXPECT_EQ(mat(0, 0), 2);
    EXPECT_EQ(mat(0, 1), 1);
    EXPECT_EQ(mat(0, 2), 3);
    EXPECT_EQ(mat(1, 0), 5);
    EXPECT_EQ(mat(1, 1), 4);
    EXPECT_EQ(mat(1, 2), 6);

}

TEST_F(MatrixTest, col_swap_not_square_greater) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 
        << 4 << 5 << 6;

    EXPECT_THROW(mat.col_swap(3, 1),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, col_swap_invalid_index) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 
        << 4 << 5 << 6;

    EXPECT_THROW(mat.col_swap(1, 3),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, col_swap_negative_index) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 << 4 << 5 << 6;

    EXPECT_THROW(mat.col_swap(1, -1),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, scalar_multiplication_matrix_times_scalar) {
    Matrix mat(2, 2);
    mat << 1.0, 2.0, 
           3.0, 4.0;
    Matrix result = mat * 2.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

TEST_F(MatrixTest, scalar_multiplication_scalar_times_matrix) {
    Matrix mat(2, 2);
    mat << 1.0, 2.0, 
           3.0, 4.0;
    Matrix result = 3.0 * mat;

    EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 6.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 9.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST_F(MatrixTest, scalar_multiplication_negative_scalar) {
    Matrix mat(2, 2);
    mat << 1.0, -2.0, 
           3.0, -4.0;
    Matrix result = mat * -1.0;

    EXPECT_DOUBLE_EQ(result(0, 0), -1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), -3.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(MatrixTest, scalar_multiplication_zero_scalar) {
    Matrix mat(2, 2);
    mat << 1.0, 2.0, 
           3.0, 4.0;
    Matrix result = mat * 0.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

TEST_F(MatrixTest, scalar_multiplication_one_scalar) {
    Matrix mat(2, 2);
    mat << 1.0, 2.0, 
           3.0, 4.0;
    Matrix result = mat * 1.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(MatrixTest, scalar_division) {
    Matrix mat(2, 2);
    mat << 4.0, 8.0, 
          12.0, 16.0;

    Matrix result = mat / 4.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(MatrixTest, scalar_division_by_one) {
    Matrix mat(2, 2);
    mat << 3.0, 6.0, 
           9.0, 12.0;

    Matrix result = mat / 1.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 6.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 9.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST_F(MatrixTest, scalar_division_fraction) {
    Matrix mat(2, 2);
    mat << 2.0, 4.0, 
           6.0, 8.0;

    Matrix result = mat / 0.5;

    EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 12.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 16.0);
}

TEST_F(MatrixTest, division_by_zero) {
    Matrix mat(2, 2);
    mat << 5.0, 10.0, 
          15.0, 20.0;

    EXPECT_THROW(mat / 0.0, astra::internals::exceptions::zero_division);
}

TEST_F(MatrixTest, scalar_division_negative_values) {
    Matrix mat(2, 2);
    mat << -10.0, -20.0, 
            30.0, 40.0;

    Matrix result = mat / 10.0;

    EXPECT_DOUBLE_EQ(result(0, 0), -1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), -2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(MatrixTest, scalar_division_small_result) {
    Matrix mat(2, 2);
    mat << 1e-6, 2e-6, 
           3e-6, 4e-6;

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

    matA << 1 << 2 
         << 3 << 4;
    matB = matA;

    EXPECT_EQ(matB(0, 0), 1);
    EXPECT_EQ(matB(0, 1), 2);
    EXPECT_EQ(matB(1, 0), 3);
    EXPECT_EQ(matB(1, 1), 4);
}

TEST_F(MatrixTest, matrix_assignment_different_size) {
    Matrix matA(2, 2);
    Matrix matB(3, 3);

    matA << 1 << 2 
         << 3 << 4;

    matB = matA;

    EXPECT_EQ(matB(0, 0), 1);
    EXPECT_EQ(matB(0, 1), 2);
    EXPECT_EQ(matB(1, 0), 3);
    EXPECT_EQ(matB(1, 1), 4);
}

TEST_F(MatrixTest, matrix_equality) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2
         << 3 << 4;

    matB << 1 << 2
         << 3 << 4;

    EXPECT_TRUE(matA == matB);
}

TEST_F(MatrixTest, matrix_equality_false) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 
         << 3 << 6;

    matB << 1 << 2 
         << 3 << 4;

    EXPECT_FALSE(matA == matB);
}

TEST_F(MatrixTest, matrix_equality_diff_size) {
    Matrix matA(2, 3);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 
         << 6 << 5 << 7;

    matB << 1 << 2 
         << 3 << 4;

    EXPECT_FALSE(matA == matB);
}

TEST_F(MatrixTest, matrix_inequality_true) {
    Matrix matA(2, 3);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 
         << 6 << 5 << 7;

    matB << 1 << 2 
         << 3 << 4;

    EXPECT_TRUE(matA != matB);
}

TEST_F(MatrixTest, matrix_inequality_false) {
    Matrix matA(2, 2);
    Matrix matB(2, 2);

    matA << 1 << 2 
         << 3 << 4;

    matB << 1 << 2 
         << 3 << 4;

    EXPECT_FALSE(matA != matB);
}


TEST_F(MatrixTest, matrix_replace) {
    Matrix mat(2, 2);

    mat << 1 << 2 
        << 3 << 4;

    mat.replace(2, 5);

    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 5);
    EXPECT_EQ(mat(1, 0), 3);
    EXPECT_EQ(mat(1, 1), 4);
}

TEST_F(MatrixTest, matrix_replace_all) { 
    Matrix mat(2, 2);
    mat << 4 << 4 
        << 4 << 4;
    
    mat.replace(4, 9);

    EXPECT_EQ(mat(0, 0), 9);
    EXPECT_EQ(mat(0, 1), 9);
    EXPECT_EQ(mat(1, 0), 9);
    EXPECT_EQ(mat(1, 1), 9);
}

TEST_F(MatrixTest, replace_nonexistent_value) {
    Matrix mat(2, 2, {1, 2, 
                      3, 4});

    mat.replace(99, 8);

    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(1, 0), 3);
    EXPECT_EQ(mat(1, 1), 4);
}

TEST_F(MatrixTest, matrix_sum_positive) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.sum(), 10);
}

TEST_F(MatrixTest, matrix_sum_negative) {
    Matrix mat(2, 2);
    mat << -1 << -2 
        << -3 << -4;

    EXPECT_DOUBLE_EQ(mat.sum(), -10);
}

TEST_F(MatrixTest, matrix_sum_zero) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << -6;

    EXPECT_DOUBLE_EQ(mat.sum(), 0);
}

TEST_F(MatrixTest, matrix_sum_large) {
    Matrix mat(2, 2);
    mat << 1e6 << 2e6 
        << 3e6 << 4e6;

    EXPECT_DOUBLE_EQ(mat.sum(), 10e6);
}

TEST_F(MatrixTest, matrix_prod_positive) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.prod(), 24);
}

TEST_F(MatrixTest, matrix_prod_negative) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << -4;

    EXPECT_DOUBLE_EQ(mat.prod(), -24);
}

TEST_F(MatrixTest, matrix_prod_zero) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << 0;

    EXPECT_DOUBLE_EQ(mat.prod(), 0);
}

TEST_F(MatrixTest, matrix_prod_large) {
    Matrix mat(2, 2);
    mat << 1e6 << 2e6 
        << 3e6 << 4e6;

    EXPECT_DOUBLE_EQ(mat.prod(), 24e24);
}

TEST_F(MatrixTest, matrix_trace_square) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.trace(), 5);
}

TEST_F(MatrixTest, matrix_trace_non_square) {
    Matrix mat(2, 3);
    mat << 1 << 2 << 3 
        << 4 << 5 << 6;

    EXPECT_THROW(mat.trace(),
                 astra::internals::exceptions::non_square_matrix);
}

TEST_F(MatrixTest, matrix_trace_singleton) { 
    Matrix mat(1, 1); 
    mat << 5;

    EXPECT_DOUBLE_EQ(mat.trace(), 5);
}

TEST_F(MatrixTest, PrincipalProd2x2) {
    Matrix mat(2, 2, {1, 2,
                      3, 4});
    EXPECT_EQ(mat.principal_prod(), 4); 
}

TEST_F(MatrixTest, PrincipalProdDiagonalMatrix) {
    Matrix mat(3, 3, { 2, 0, 0, 
                       0, 3, 0, 
                       0, 0, 5 }
               );
    EXPECT_EQ(mat.principal_prod(), 30); 
}

TEST_F(MatrixTest, matrix_avg_positive) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.avg(), 2.5);
}

TEST_F(MatrixTest, matrix_avg_negative) {
    Matrix mat(2, 2);
    mat << -1 << -2 
        << -3 << -4;

    EXPECT_DOUBLE_EQ(mat.avg(), -2.5);
}

TEST_F(MatrixTest, matrix_avg_zero) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << -6;

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
    mat << 1 << 0 
        << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.min(), 0);
}

TEST_F(MatrixTest, matrix_min_same) {
    Matrix mat(2, 2);
    mat << 1 << 1 
        << 1 << 1;

    EXPECT_DOUBLE_EQ(mat.min(), 1);
}

TEST_F(MatrixTest, matrix_max_same) {
    Matrix mat(2, 2);
    mat << 1 << 1 
        << 1 << 1;

    EXPECT_DOUBLE_EQ(mat.max(), 1);
}

TEST_F(MatrixTest, matrix_max_singleton) {
    Matrix mat(1, 1);
    mat << -6;

    EXPECT_DOUBLE_EQ(mat.max(), -6);
}

TEST_F(MatrixTest, matrix_max_zero) {
    Matrix mat(2, 2);
    mat << -10 << 0 
        << -45 << -1;

    EXPECT_DOUBLE_EQ(mat.max(), 0);
}

TEST_F(MatrixTest, matrix_max_positive) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << 4;

    EXPECT_DOUBLE_EQ(mat.max(), 4);
}

TEST_F(MatrixTest, matrix_max_negative) {
    Matrix mat(2, 2);
    mat << -1 << -2 
        << -3 << -4;

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

TEST_F(MatrixTest, is_identity_true) {
    Matrix mat = Matrix::identity(3);
    EXPECT_TRUE(mat.is_identity());

}

TEST_F(MatrixTest, is_identity_false) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << 4;
    EXPECT_FALSE(mat.is_identity());
}

TEST_F(MatrixTest, is_identity_non1) { 
    Matrix mat(2, 2); 
    mat << 2 << 0
        << 0 << 2;
    EXPECT_FALSE(mat.is_identity());
}

TEST_F(MatrixTest, is_symmetric_true) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 2 << 5;
    EXPECT_TRUE(mat.is_symmetric());
}

TEST_F(MatrixTest, is_symmetric_false) {
    Matrix mat(2, 2);
    mat << 1 << 2 
        << 3 << 4;
    EXPECT_FALSE(mat.is_symmetric());
}

TEST_F(MatrixTest, true_diagonal_matrix) {
    Matrix diag_matrix(3, 3, {1, 0, 0, 
                              0, 2, 0, 
                              0, 0, 3});
    EXPECT_TRUE(diag_matrix.is_diagonal());
}

TEST_F(MatrixTest, false_diagonal_matrix) {
    Matrix non_diag_matrix(3, 3, {1, 2, 0, 
                                  0, 2, 0, 
                                  0, 1, 3});
    EXPECT_FALSE(non_diag_matrix.is_diagonal());
}

TEST_F(MatrixTest, single_element_matrix) {
    Matrix single_element_matrix(1, 1, {5});
    EXPECT_TRUE(single_element_matrix.is_diagonal());
}

TEST_F(MatrixTest, non_square_matrix) {
    Matrix non_square_matrix(2, 3, {1, 0, 0, 
                                    0, 2, 0});
    EXPECT_FALSE(non_square_matrix.is_diagonal());
}

TEST_F(MatrixTest, true_upper_triangular_matrix) {
    Matrix upper_triangular_matrix(3, 3, {1, 2, 3, 
                                          0, 5, 6, 
                                          0, 0, 9});
    EXPECT_TRUE(upper_triangular_matrix.is_upper_triangular());
}

TEST_F(MatrixTest, zero_upper_triangular_matrix) {
    Matrix zero_upper_triangular_matrix(3, 3, {0, 2, 3, 
                                               0, 0, 6, 
                                               0, 0, 0});
    EXPECT_TRUE(zero_upper_triangular_matrix.is_upper_triangular());
}

TEST_F(MatrixTest, upper_triangular_with_zero_on_diagonal) {
    Matrix zero_diag_upper_triangular_matrix(3, 3, {1, 2, 3, 
                                                    0, 0, 6, 
                                                    0, 0, 9});
    EXPECT_TRUE(zero_diag_upper_triangular_matrix.is_upper_triangular());
}

TEST_F(MatrixTest, true_lower_triangular_matrix) {
    Matrix lower_triangular_matrix(3, 3, 
        {
            1, 0, 0, 
            4, 5, 0, 
            7, 8, 9
        }
    );
    EXPECT_TRUE(lower_triangular_matrix.is_lower_triangular());
}

TEST_F(MatrixTest, zero_lower_triangular_matrix) {
    Matrix zero_lower_triangular_matrix(3, 3, {0, 0, 0, 
                                               4, 0, 0, 
                                               7, 8, 0});
    EXPECT_TRUE(zero_lower_triangular_matrix.is_lower_triangular());
}

TEST_F(MatrixTest, lower_triangular_with_zero_on_diagonal) {
    Matrix zero_diag_lower_triangular_matrix(3, 3, {1, 0, 0, 
                                                    4, 0, 0,
                                                    7, 8, 0});
    EXPECT_TRUE(zero_diag_lower_triangular_matrix.is_lower_triangular());
}

TEST_F(MatrixTest, identity_matrix_is_triangular) {
    Matrix identity_matrix(3, 3, {1, 0, 0, 
                                  0, 1, 0, 
                                  0, 0, 1});
    EXPECT_TRUE(identity_matrix.is_triangular());
    EXPECT_TRUE(identity_matrix.is_upper_triangular());
    EXPECT_TRUE(identity_matrix.is_lower_triangular());
    EXPECT_TRUE(identity_matrix.is_diagonal());
}

TEST_F(MatrixTest, zero_matrix_is_triangular_and_diagonal) {
    Matrix zero_matrix(3, 3, {0, 0, 0, 
                              0, 0, 0, 
                              0, 0, 0});
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
    Matrix matA = Matrix(2, 2, {1.0, 2.0, 
                                3.0, 4.0});
    Matrix matB = Matrix(2, 3, {5.0, 6.0, 7.0, 
                                8.0, 9.0, 10.0});

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
    Matrix matA = Matrix(2, 2, {1.0, 2.0, 
                                3.0, 4.0});
    Matrix matB = Matrix(3, 2, {5.0, 6.0, 
                                7.0, 8.0, 
                                9.0, 10.0});

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
    Matrix matA = Matrix(3, 1, {1.0, 
                                2.0, 
                                3.0});
    Matrix matB = Matrix(3, 2, {4.0, 5.0, 
                                6.0, 7.0, 
                                8.0, 9.0});

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
    double valuesA[] = {1,  2,  3,  4, 
                        5,  6,  7,  8, 
                        9, 10, 11, 12, 
                       13, 14, 15, 16};
    Matrix matA(4, 4, valuesA);

    double valuesB[] = {17, 18, 19, 20, 
                        21, 22, 23, 24};
    Matrix matB(4, 2, valuesB);

    matA.join(matB);

    EXPECT_EQ(matA.num_row(), 4);
    EXPECT_EQ(matA.num_col(), 6);

    EXPECT_DOUBLE_EQ(matA(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(matA(0, 4), 17.0);
    EXPECT_DOUBLE_EQ(matA(3, 5), 24.0);
}

TEST_F(MatrixTest, matrix_join_with_empty_other_matrix) {
    Matrix matA = Matrix(2, 2, {1.0, 2.0, 
                                3.0, 4.0});
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
    Matrix matA = Matrix(2, 2, {-1.0, -2.0, 
                                -3.0, -4.0});

    Matrix matB = Matrix(2, 2, {5.0, -6.0,
                                7.0, -8.0});

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

TEST_F(MatrixTest, valid_submatrix) {
    Matrix mat(4, 4, 
        {
            1, 2, 3, 4, 
            5, 6, 7, 8, 
            9, 10, 11, 12, 
            13, 14, 15, 16
        }
    );

    Matrix submat = mat.submatrix(1, 1, 2, 2);
    Matrix expected(2, 2, 
        {
            6,  7, 
           10, 11
        }
    );

    EXPECT_EQ(submat, expected);
}

TEST_F(MatrixTest, submatrix_out_of_bounds) {
    Matrix mat(4, 4, 
        {  
            1,  2,  3,  4, 
            5,  6,  7,  8, 
            9, 10, 11, 12, 
           13, 14, 15, 16
        }
    );

    EXPECT_THROW(mat.submatrix(1, 1, 5, 5),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, submatrix_invalid) {

    Matrix mat(4, 4, 
        {
            1,  2,  3,  4, 
            5,  6,  7,  8, 
            9, 10, 11, 12, 
            13, 14, 15, 16
        }
    );

    EXPECT_THROW(mat.submatrix(1, 1, 0, 0),
                 astra::internals::exceptions::invalid_argument);
}

TEST_F(MatrixTest, submatrix_single_element) {
    Matrix mat(1, 1, {5});

    Matrix submat = mat.submatrix(0, 0, 0, 0);

    EXPECT_EQ(submat, mat);
}

TEST_F(MatrixTest, submatrix_single_row) {
    Matrix mat(1, 3, 
        {
            1, 
            2, 
            3
        }
    );

    Matrix submat = mat.submatrix(0, 0, 0, 2);

    EXPECT_EQ(submat, mat);
}

TEST_F(MatrixTest, submatrix_single_column) {
    Matrix mat(3, 1, {1, 2, 3});

    Matrix submat = mat.submatrix(0, 0, 2, 0);

    EXPECT_EQ(submat, mat);
}

TEST_F(MatrixTest, rref_singleton) {
    Matrix singleton(1, 1, {5});
    Matrix rref = singleton.rref();

    Matrix expected(1, 1, {1});

    EXPECT_EQ(rref, expected);
}

TEST_F(MatrixTest, rref_zero) {
    Matrix zero(2, 2);
    Matrix rref = zero.rref();

    EXPECT_EQ(rref, zero);
}

TEST_F(MatrixTest, rref_identity) {
    Matrix identity = Matrix::identity(3);
    Matrix rref = identity.rref();

    EXPECT_EQ(rref, identity);
}

TEST_F(MatrixTest, rref_diagonal) {
    Matrix diagonal(3, 3, {1, 0, 0, 
                           0, 2, 0, 
                           0, 0, 3});

    Matrix rref = diagonal.rref();

    Matrix expected(3, 3, {1, 0, 0, 
                           0, 1, 0, 
                           0, 0, 1});

    EXPECT_EQ(rref, expected);
}

TEST_F(MatrixTest, rref_upper_triangular) {
    Matrix upper_triangular(3, 3, {1, 2, 3,
                                   0, 5, 6, 
                                   0, 0, 9});

    Matrix rref = upper_triangular.rref();
    Matrix expected = Matrix::identity(3);

    EXPECT_EQ(rref, expected);
}

TEST_F(MatrixTest, rref_lower_triangular) {
    Matrix lower_triangular(3, 3, {1, 0, 0, 
                                   4, 5, 0,
                                   7, 8, 9});

    Matrix rref = lower_triangular.rref();
    Matrix expected = Matrix::identity(3);

    EXPECT_EQ(rref, expected);
}

TEST_F(MatrixTest, rref_non_square) {
    Matrix non_square(2, 3, {1, 2, 3, 
                             4, 5, 6});

    Matrix rref = non_square.rref();

    Matrix expected(2, 3, {1, 0, -1, 
                           0, 1, 2});

    EXPECT_EQ(rref, expected);
}

TEST_F(MatrixTest, rref_non_square2) {
    Matrix non_square(3, 2, {1, 2, 
                             3, 4,
                             5, 6});

    Matrix rref = non_square.rref();

    Matrix expected(3, 2, {1, 0, 
                           0, 1, 
                           0, 0});

    EXPECT_EQ(rref, expected);
}

TEST_F(MatrixTest, get_row) {
    Matrix mat(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

    Vector row = mat.get_row(1); 
    EXPECT_EQ(row.get_size(), 3);
    EXPECT_EQ(row[0], 4);
    EXPECT_EQ(row[1], 5);
    EXPECT_EQ(row[2], 6);

    EXPECT_THROW(mat.get_row(-1),
                 astra::internals::exceptions::index_out_of_range);
    EXPECT_THROW(mat.get_row(3),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, get_col) {
    Matrix mat(3, 3, 
        {
            1, 2, 3, 
            4, 5, 6, 
            7, 8, 9
        }
    );

    Vector row = mat.get_col(2);
    EXPECT_EQ(row.get_size(), 3);
    EXPECT_EQ(row[0], 3);
    EXPECT_EQ(row[1], 6);
    EXPECT_EQ(row[2], 9);

    EXPECT_THROW(mat.get_row(-1),
                 astra::internals::exceptions::index_out_of_range);
    EXPECT_THROW(mat.get_row(3),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, is_pivot_col) {
    Matrix mat(3, 3, 
        {
            1, 2, 0, 
            0, 1, 3, 
            0, 0, 1
        }
    );
    EXPECT_TRUE(mat.is_pivot_col(0));
    EXPECT_TRUE(mat.is_pivot_col(1));
    EXPECT_TRUE(mat.is_pivot_col(2));

    Matrix non_pivot(3, 3, {1, 2, 3, 0, 0, 0, 0, 0, 0});
    EXPECT_FALSE(non_pivot.is_pivot_col(1));

    EXPECT_THROW(mat.is_pivot_col(-1),
                 astra::internals::exceptions::index_out_of_range);
    EXPECT_THROW(mat.is_pivot_col(3),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, is_pivot_row) {
    // Full rank RREF matrix
    Matrix mat1(3, 3, 
        {
            1, 0, 0, 
            0, 1, 0, 
            0, 0, 1
        }
    );
    EXPECT_TRUE(mat1.is_pivot_row(0)); // Row 0 contains a pivot
    EXPECT_TRUE(mat1.is_pivot_row(1)); // Row 1 contains a pivot
    EXPECT_TRUE(mat1.is_pivot_row(2)); // Row 2 contains a pivot

    // Zero row and non-pivot row
    Matrix mat2(3, 3, 
        {
            1, 2, 3, 
            0, 0, 0, 
            0, 0, 0
        }
    );
    EXPECT_FALSE(mat2.is_pivot_row(1)); // Row 1 is zero
    EXPECT_FALSE(mat2.is_pivot_row(2)); // Row 2 is zero

    // Partially reduced matrix
    Matrix mat3(3, 3, 
        {
            1, 0, 2, 
            0, 1, 0, 
            0, 0, 0
        }
    );
    EXPECT_TRUE(mat3.is_pivot_row(0));  // Row 0 has a valid pivot
    EXPECT_TRUE(mat3.is_pivot_row(1));  // Row 1 has a valid pivot
    EXPECT_FALSE(mat3.is_pivot_row(2)); // Row 2 is zero

    // Boundary tests
    EXPECT_THROW(mat1.is_pivot_row(-1),
                 astra::internals::exceptions::index_out_of_range);
    EXPECT_THROW(mat1.is_pivot_row(3),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, is_zero_row_true) {
    Matrix zero_row(1, 3, {0, 0, 0});

    EXPECT_TRUE(zero_row.is_zero_row(0));

}

TEST_F(MatrixTest, is_zero_row_false) {
    Matrix non_zero_row(1, 3, {0, 0, 1});

    EXPECT_FALSE(non_zero_row.is_zero_row(0));
}

TEST_F(MatrixTest, is_zero_row_out_of_bounds) {
    Matrix zero_row(1, 3, {0, 0, 0});

    EXPECT_THROW(zero_row.is_zero_row(-1),
                 astra::internals::exceptions::index_out_of_range);
    EXPECT_THROW(zero_row.is_zero_row(1),
                 astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, is_zero_col_true) {
    Matrix zero_col(3, 3, {0, 7, 20,
                           0, 2, 3,
                           0, 9, 4});

    EXPECT_TRUE(zero_col.is_zero_col(0));
}

TEST_F(MatrixTest, is_zero_col_false) {
    Matrix non_zero_col(3, 3, {0, 1, 6, 
                               0, 2, 9, 
                               0, 3, 4});

    EXPECT_FALSE(non_zero_col.is_zero_col(1));
}

TEST_F(MatrixTest, is_zero_col_out_of_bounds) {
    Matrix zero_col(3, 3, {0, 0, 0, 
                           1, 2, 3, 
                           6, 9, 4});

    EXPECT_THROW(zero_col.is_zero_col(-1),
                 astra::internals::exceptions::index_out_of_range);
    EXPECT_THROW(zero_col.is_zero_col(3),
                 astra::internals::exceptions::index_out_of_range);
}
TEST_F(MatrixTest, rank_full_rank_square_matrix) {
    Matrix mat1(3, 3, 
        {
            1, 0, 0, 
            0, 1, 0, 
            0, 0, 1
        }
    );
    EXPECT_EQ(mat1.rank(), 3); 
}

TEST_F(MatrixTest, rank_rectangular_matrix) {
    Matrix mat2(3, 3, {1, 2, 3, 
                       0, 0, 0, 
                       4, 5, 6});
    EXPECT_EQ(mat2.rank(), 2); 
}

TEST_F(MatrixTest, rank_zero_matrix) {
    Matrix mat3(3, 3, {0, 0, 0, 
                       0, 0, 0,     
                       0, 0, 0});
    EXPECT_EQ(mat3.rank(), 0); 
}

TEST_F(MatrixTest, rank_non_square_matrix) {
    Matrix mat4(2, 3, {1, 2, 3, 
                       4, 5, 6});
    EXPECT_EQ(mat4.rank(), 2); 
}

TEST_F(MatrixTest, determinant_2x2) {
    Matrix mat(2, 2,{ 1, 2, 
                      3, 4 });

    EXPECT_EQ(mat.det(), -2); // det = 1*4 - 2*3 = -2
}

TEST_F(MatrixTest, determinant_identity_matrix) {
    Matrix identity(3, 3, {1, 0, 0, 
                           0, 1, 0, 
                           0, 0, 1});

    EXPECT_EQ(identity.det(), 1); // Determinant of identity matrix is 1
}

TEST_F(MatrixTest, determinant_singular_matrix) {
    Matrix singular(2, 2, {1, 2, 
                           2, 4});

    EXPECT_EQ(singular.det(), 0); // Rows are linearly dependent, determinant is 0
}

TEST_F(MatrixTest, determinant_nonsquare_matrix) {
    Matrix non_square(2, 3, {1, 2, 3,
                             4, 5, 6});

    EXPECT_THROW(non_square.det(), astra::internals::exceptions::non_square_matrix);
}

TEST_F(MatrixTest, determinant_3x3) {
    Matrix mat(3, 3, {6, 1, 1, 
                      4, -2, 5,
                      2, 8, 7});

    EXPECT_EQ(mat.det(), -306); 
}

TEST_F(MatrixTest, another_determinant_3x3) {
    Matrix mat(3, 3, {3, 7, 0, 
                      8, 0, -2, 
                      0, -4, -5});

    EXPECT_EQ(mat.det(), 256);
}

TEST_F(MatrixTest, determinant_with_row_swaps) {
    Matrix mat(2, 2, {0, 1, 
                      1, 0}); 

    EXPECT_EQ(mat.det(), -1);    
}

TEST_F(MatrixTest, inverse_nonSquare) {
    Matrix mat(2, 3, {1, 2, 3, 
                      4, 5, 6});

    EXPECT_THROW(mat.inv(),
                 astra::internals::exceptions::non_square_matrix);
}

TEST_F(MatrixTest, is_singular_square) {
    Matrix singular(2, 2, {1, 2, 
                           2, 4});

    EXPECT_TRUE(singular.is_singular());
}

TEST_F(MatrixTest, is_singular_identity) {
    Matrix identity(3, 3, {1, 0, 0, 
                           0, 1, 0, 
                           0, 0, 1});

    EXPECT_FALSE(identity.is_singular());
}

TEST_F(MatrixTest, is_singular_zero) {
    Matrix zero(2, 2);

    EXPECT_TRUE(zero.is_singular());
}

TEST_F(MatrixTest, is_singular_non_square) {
    Matrix non_square(2, 3, {1, 2, 3, 
                             4, 5, 6});

    EXPECT_THROW(non_square.is_singular(),
                 astra::internals::exceptions::non_square_matrix);
}

TEST_F(MatrixTest, is_singular_3x3) {
    Matrix singular(3, 3, {1, 2, 3, 
                           4, 5, 6, 
                           7, 8, 9});

    EXPECT_TRUE(singular.is_singular());
}

TEST_F(MatrixTest, inverse_singular) {
    Matrix singular(2, 2, {1, 2, 
                           2, 4});

    EXPECT_THROW(singular.inv(),
                 astra::internals::exceptions::singular_matrix);
}

TEST_F(MatrixTest, inverse_identity) {
    Matrix identity(3, 3, {1, 0, 0,
                           0, 1, 0, 
                           0, 0, 1});

    Matrix inverse = identity.inv();

    EXPECT_EQ(inverse, identity);
}

TEST_F(MatrixTest, inverse_2x2) {
    Matrix mat(2, 2, {1, 2, 
                      3, 4});

    Matrix inverse = mat.inv();

    Matrix expected(2, 2, {-2, 1, 
                          1.5, -0.5});

    EXPECT_EQ(inverse, expected);
}

TEST_F(MatrixTest, inverse_3x3) {
    Matrix mat(3, 3, {1, 2, 3, 
                      0, 1, 4,
                      5, 6, 0});
    Matrix inverse = mat.inv();

    Matrix expected(3, 3,
                    {-24, 18, 5, 
                     20, -15, -4, 
                     -5, 4, 1});

    EXPECT_EQ(inverse, expected);
}

TEST_F(MatrixTest, inverse_singleton) {
    Matrix singleton(1, 1, {5});
    Matrix inverse = singleton.inv();

    Matrix expected(1, 1, {0.2});

    EXPECT_EQ(inverse, expected);
}

TEST_F(MatrixTest, single_row_submatrix) {
    Matrix mat(3, 3, {1, 2, 3, 
                      4, 5, 6, 
                      7, 8, 9});

    Matrix submat = mat.submatrix(1, 0, 1, 2);
    Matrix expected(1, 3, {4, 5, 6});

    EXPECT_EQ(submat, expected);
}

TEST_F(MatrixTest, single_column_submatrix) {
    Matrix mat(3, 3, {1, 2, 3, 
                      4, 5, 6, 
                      7, 8, 9});

    Matrix submat = mat.submatrix(0, 1, 2, 1);
    Matrix expected(3, 1, {2, 
                           5, 
                           8});

    EXPECT_EQ(submat, expected);
}

TEST_F(MatrixTest, one_by_one_submatrix) {
    Matrix mat(3, 3, {1, 2, 3,
                      4, 5, 6, 
                      7, 8, 9});

    Matrix submat = mat.submatrix(1, 1, 1, 1);
    Matrix expected(1, 1, {5});

    EXPECT_EQ(submat, expected);
}

TEST_F(MatrixTest, out_of_bounds_submatrix) {
    Matrix mat(3, 3, {1, 2, 3, 
                      4, 5, 6, 
                      7, 8, 9});

    EXPECT_THROW(mat.submatrix(-1, 0, 1, 1), astra::internals::exceptions::index_out_of_range);
    EXPECT_THROW(mat.submatrix(0, 0, 3, 3), astra::internals::exceptions::index_out_of_range);
}

TEST_F(MatrixTest, reverse_indices_submatrix) {
    Matrix mat(3, 3, {1, 2, 3, 
                      4, 5, 6, 
                      7, 8, 9});

    EXPECT_THROW(mat.submatrix(2, 2, 1, 1), astra::internals::exceptions::invalid_argument);
}

TEST_F(MatrixTest, nullspace_zero_matrix) {
    Matrix zeroMat(3, 3, {0, 0, 0, 
                          0, 0, 0, 
                          0, 0, 0}); // 3x3 zero matrix
    Matrix nullspace = zeroMat.nullspace();

    // Nullspace should have 3 basis vectors, each a unit vector
    EXPECT_EQ(nullspace.num_row(), 3);
    EXPECT_EQ(nullspace.num_col(), 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                EXPECT_DOUBLE_EQ(nullspace(i, j), 1.0);
            }
            else {
                EXPECT_DOUBLE_EQ(nullspace(i, j), 0.0);
            }
        }
    }
}

TEST_F(MatrixTest, nullspace_singular_matrix) {
    Matrix A(3, 3, {2, 4, 8, 
                    1, 2, 4, 
                    0, 0, 0});
    Matrix nullspace = A.nullspace();

    // The nullspace should contain one basis vector
    EXPECT_EQ(nullspace.num_row(), 3);
    EXPECT_EQ(nullspace.num_col(), 2);
}

TEST_F(MatrixTest, nullspace_identity_matrix) {
    Matrix identity(3, 3, {1, 0, 0, 
                           0, 1, 0, 
                           0, 0, 1});
    Matrix nullspace = identity.nullspace();

    // The nullspace should be a 3x1 matrix
    EXPECT_EQ(nullspace.num_row(), 3);
    EXPECT_EQ(nullspace.num_col(), 1);
    EXPECT_TRUE(nullspace.is_zero());
}

TEST_F(MatrixTest, nullspace_2x2) {
    Matrix A(2, 2, {1, 2, 
                    2, 4});

    Matrix nullspace = A.nullspace();

    // The nullspace should contain one basis vector
    EXPECT_EQ(nullspace.num_row(), 2);
    EXPECT_EQ(nullspace.num_col(), 1);
}

TEST_F(MatrixTest, nullspace_3x3) {
    Matrix A(3, 3, {1, 2, 3, 
                    4, 5, 6, 
                    7, 8, 9});

    Matrix nullspace = A.nullspace();

    // The nullspace should contain one basis vector
    EXPECT_EQ(nullspace.num_row(), 3);
    EXPECT_EQ(nullspace.num_col(), 1);
}

TEST_F(MatrixTest, nullspace_singleton) {
    Matrix singleton(1, 1, {5});
    Matrix nullspace = singleton.nullspace();

    // The nullspace should be a 1x1 matrix
    EXPECT_EQ(nullspace.num_row(), 1);
    EXPECT_EQ(nullspace.num_col(), 1);
    EXPECT_TRUE(nullspace.is_zero());
}

TEST_F(MatrixTest, nullspace_non_square) {
    Matrix A(2, 3, {1, 2, 3, 
                    4, 5, 6});

    Matrix nullspace = A.nullspace();

    // The nullspace should contain one basis vector
    EXPECT_EQ(nullspace.num_row(), 3);
    EXPECT_EQ(nullspace.num_col(), 1);

}

TEST_F(MatrixTest, nullspace_linearly_dependent) {
    Matrix A(3, 3, {1, 2, 3, 
                    2, 4, 6, 
                    3, 6, 9});

    Matrix nullspace = A.nullspace();

    // The nullspace should contain one basis vector
    EXPECT_EQ(nullspace.num_row(), 3);
    EXPECT_EQ(nullspace.num_col(), 2);


}

TEST_F(MatrixTest, nullspace_full_rank) {
    Matrix A(3, 2, {1, 0, 
                    0, 1, 
                    0, 0});

    Matrix nullspace = A.nullspace();

    // The nullspace should be a 2x1 matrix
    EXPECT_EQ(nullspace.num_row(), 2);
    EXPECT_EQ(nullspace.num_col(), 1);
    EXPECT_TRUE(nullspace.is_zero());
}

TEST_F(MatrixTest, nullspace_hilbert_matrix) {
    Matrix A(3, 3,
             {1      , 1.0 / 2, 1.0 / 3, 
              1.0 / 2, 1.0 / 3, 1.0 / 4, 
              1.0 / 3, 1.0 / 4, 1.0 / 5});

    Matrix nullspace = A.nullspace();

    // The nullspace should be a 3x1 matrix
    EXPECT_EQ(nullspace.num_row(), 3);
    EXPECT_EQ(nullspace.num_col(), 1);
    EXPECT_TRUE(nullspace.is_zero());
}





} // namespace astra