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

} // namespace astra