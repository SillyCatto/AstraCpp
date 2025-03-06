#include "pch.h"

#include <iostream>
#include "gtest/gtest.h"

#include "Vector.h"
#include "Matrix.h"
#include "Solver.h"
#include "Exceptions.h"
#include "MathUtils.h"

namespace astra {

// Test fixture class for Decomposer
class DecomposerTest : public ::testing::Test {
  protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(DecomposerTest, square_matrix) {
    
    Matrix mat(3, 3,
        { 
            2, 1, 1, 
            4, -6, 0,
            -2, 7, 2 
        }
    );
    
    auto result = Decomposer::palu(mat);

    EXPECT_EQ(result.P * result.L * result.U, mat);
    EXPECT_EQ(result.P.num_row(), result.P.num_col());
    EXPECT_EQ(result.L.num_row(), result.L.num_col());
    EXPECT_EQ(result.U.num_row(), result.U.num_col());

    EXPECT_TRUE(result.L.is_lower_triangular());
    EXPECT_TRUE(result.U.is_upper_triangular());
}

TEST_F(DecomposerTest, non_invertible_matrix) {

    Matrix mat(3, 3, 
        {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        }
    );

    auto result = Decomposer::palu(mat);

    EXPECT_EQ(result.U.principal_prod(), 0.0);
    EXPECT_EQ(result.swaps % 2, 0);
}

TEST_F(DecomposerTest, identity_matrix) {
   
    Matrix mat = Matrix::identity(4);

    auto result = Decomposer::palu(mat);

    EXPECT_EQ(result.P, Matrix::identity(4));
    EXPECT_EQ(result.L, Matrix::identity(4));
    EXPECT_EQ(result.U, Matrix::identity(4));
    EXPECT_EQ(result.swaps, 0);
    EXPECT_TRUE(result.L.is_lower_triangular());
    EXPECT_TRUE(result.U.is_upper_triangular());
        
}

TEST_F(DecomposerTest, singleton_matrix) {

    Matrix mat(1, 1, {1});

    auto result = Decomposer::palu(mat);

    EXPECT_EQ(result.P, Matrix::identity(1));
    EXPECT_EQ(result.L, Matrix::identity(1));
    EXPECT_EQ(result.U, mat);
    EXPECT_EQ(result.swaps, 0);
    EXPECT_TRUE(result.L.is_lower_triangular());
    EXPECT_TRUE(result.U.is_upper_triangular());
}

TEST_F(DecomposerTest, zero_matrix) {

    Matrix mat(3, 3, {0, 0, 0, 
                      0, 0, 0, 
                      0, 0, 0});

    auto result = Decomposer::palu(mat);

    EXPECT_EQ(result.P, Matrix::identity(3));
    EXPECT_EQ(result.L, Matrix::identity(3));
    EXPECT_EQ(result.U, mat);
    EXPECT_EQ(result.swaps, 0);
    EXPECT_TRUE(result.L.is_lower_triangular());
    EXPECT_TRUE(result.U.is_upper_triangular());
}

TEST_F(DecomposerTest, non_square_matrix) {

    Matrix mat(2, 3, {1, 2, 3, 
                      4, 5, 6});

    EXPECT_THROW(Decomposer::palu(mat),
                 internals::exceptions::non_square_matrix);
}

TEST_F(DecomposerTest, upper_triangular_matrix) {

    Matrix mat(3, 3, {1, 2, 3, 
                      0, 4, 5,
                      0, 0, 6});

    auto result = Decomposer::palu(mat);

    EXPECT_EQ(result.P, Matrix::identity(3));
    EXPECT_EQ(result.L, Matrix::identity(3));
    EXPECT_EQ(result.U, mat);
    EXPECT_EQ(result.swaps, 0);
    EXPECT_TRUE(result.L.is_lower_triangular());
    EXPECT_TRUE(result.U.is_upper_triangular());
}

TEST_F(DecomposerTest, lower_triangular_matrix) {

    Matrix mat(3, 3, {1, 0, 0, 
                      2, 5, 0, 
                      4, 5, 6});

    auto result = Decomposer::palu(mat);

    Matrix ans = result.P * result.L * result.U;

    EXPECT_EQ(ans, mat);
    EXPECT_TRUE(result.L.is_lower_triangular());
    EXPECT_TRUE(result.U.is_upper_triangular());
}






} // namespace astra