#include "pch.h"

#include <iostream>
#include "gtest/gtest.h"

#include "Vector.h"
#include "Matrix.h"
#include "Solver.h"
#include "Exceptions.h"
#include "MathUtils.h"

namespace astra {

// Test fixture class for Solver
class SolverTest : public ::testing::Test {
  protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(SolverTest, eqn_solve_test_1) { 
    Matrix coeff_mat(4, 4, {1, 2, -1, 5,
                            3, 6, -3, -2,
                            7, -5, 3, -1,
                            5, 10, 2, -7});


    Vector constants{22, -2, 2, 3};

    Vector actual_ans = Solver::solve(coeff_mat, constants);
    Vector expected_ans{1, 2, 3, 4};

    EXPECT_EQ(actual_ans, expected_ans);
}


} // namespace astra