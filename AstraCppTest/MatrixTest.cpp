#include "pch.h"

#include "Matrix.h"
#include "gtest/gtest.h"

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
    EXPECT_THROW(Matrix(-2, 3), std::invalid_argument);
    EXPECT_THROW(Matrix(2, 0), std::invalid_argument);
    EXPECT_THROW(Matrix(0, 0), std::invalid_argument);
}

TEST_F(MatrixTest, comma_initializer) {
    Matrix m(2, 2);
    m << 1.0, 2.0, 3.0, 4.0;

    EXPECT_EQ(m(0, 0), 1.0);
    EXPECT_EQ(m(0, 1), 2.0);
    EXPECT_EQ(m(1, 0), 3.0);
    EXPECT_EQ(m(1, 1), 4.0);
}

} // namespace astra