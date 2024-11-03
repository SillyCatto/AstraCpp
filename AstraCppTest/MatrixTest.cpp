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

TEST_F(MatrixTest, MatrixAddition) {
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

TEST_F(MatrixTest, MatrixAdditionSizeMismatch) {
    Matrix matA(2, 2);
    Matrix matB(3, 3);

    matA << 1 << 2 << 3 << 4; 

    EXPECT_THROW(matA + matB, astra::internals::exceptions::matrix_size_mismatch);
}

TEST_F(MatrixTest, MatrixAdditionEmpty) {
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

TEST_F(MatrixTest, MatrixSubtraction) {
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

TEST_F(MatrixTest, MatrixSubtractionSizeMismatch) {
    Matrix matA(3, 3);
    Matrix matB(2, 2);

    matA << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9; 

    EXPECT_THROW(matA - matB, astra::internals::exceptions::matrix_size_mismatch);
}

TEST_F(MatrixTest, MatrixSubtractionEmpty) {
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

TEST_F(MatrixTest, ScalarDivision) {
    Matrix mat(2, 2);
    mat << 4.0, 8.0, 12.0, 16.0;

    Matrix result = mat / 4.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(MatrixTest, ScalarDivisionByOne) {
    Matrix mat(2, 2);
    mat << 3.0, 6.0, 9.0, 12.0;

    Matrix result = mat / 1.0;

    EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 6.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 9.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST_F(MatrixTest, ScalarDivisionFraction) {
    Matrix mat(2, 2);
    mat << 2.0, 4.0, 6.0, 8.0;

    Matrix result = mat / 0.5;

    EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 12.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 16.0);
}

TEST_F(MatrixTest, DivisionByZero) {
    Matrix mat(2, 2);
    mat << 5.0, 10.0, 15.0, 20.0;

    EXPECT_THROW(mat / 0.0, astra::internals::exceptions::zero_division);
}

TEST_F(MatrixTest, ScalarDivisionNegativeValues) {
    Matrix mat(2, 2);
    mat << -10.0, -20.0, 30.0, 40.0;

    Matrix result = mat / 10.0;

    EXPECT_DOUBLE_EQ(result(0, 0), -1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), -2.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST_F(MatrixTest, ScalarDivisionSmallResult) {
    Matrix mat(2, 2);
    mat << 1e-6, 2e-6, 3e-6, 4e-6;

    Matrix result = mat / 1e6;

    EXPECT_DOUBLE_EQ(result(0, 0), 1e-12);
    EXPECT_DOUBLE_EQ(result(0, 1), 2e-12);
    EXPECT_DOUBLE_EQ(result(1, 0), 3e-12);
    EXPECT_DOUBLE_EQ(result(1, 1), 4e-12);
}

} // namespace astra