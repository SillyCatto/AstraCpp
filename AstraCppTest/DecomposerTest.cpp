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



} // namespace astra