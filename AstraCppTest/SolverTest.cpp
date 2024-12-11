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

TEST_F(SolverTest, eqn_solve_test_2) {
    Matrix coeff_mat(3, 3, {1, 2, 3, 
                            4, 5, 6, 
                            7, 8, 10}
    );

    Vector constants{14, 32, 50};
    Vector actual_ans = Solver::solve(coeff_mat, constants);
    Vector expected_ans{-2, 8, 0};

    EXPECT_EQ(actual_ans, expected_ans);
    
}

TEST_F(SolverTest, eqn_solve_test_3) {
    Matrix coeff_mat(2, 2, {1, -1, 
                            5, 3}
    );

    Vector constants{5, 9};
    Vector actual_ans = Solver::solve(coeff_mat, constants);
    Vector expected_ans{3, -2};

    EXPECT_EQ(actual_ans, expected_ans);
}

TEST_F(SolverTest, eqn_solve_test_4) {
    Matrix coeff_mat(2, 2, {2, 4,
                            4, -4}
    );

    Vector constants{14, 4};
    Vector actual_ans = Solver::solve(coeff_mat, constants);
    Vector expected_ans{3, 2};

    EXPECT_EQ(actual_ans, expected_ans);
}

TEST_F(SolverTest, eqn_solve_test_5_invalid) {
    Matrix coeff_mat(2, 3, {1, 2, 3, 
                            4, 9, 11}
    );

    Vector constants{5, 9};
    EXPECT_THROW(Solver::solve(coeff_mat, constants),
                 internals::exceptions::non_square_matrix);
}

TEST_F(SolverTest, eqn_solve_test_6_invalid) {
    Matrix coeff_mat(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 10});

    Vector constants{14, 32};
    EXPECT_THROW(Solver::solve(coeff_mat, constants),
                 internals::exceptions::variable_and_value_number_mismatch);
}

TEST_F(SolverTest, eqn_solve_test_7_singleton) {
    Matrix coeff_mat(1, 1, {5});

    Vector constants{10};
    Vector actual_ans = Solver::solve(coeff_mat, constants);
    Vector expected_ans{2};

    EXPECT_EQ(actual_ans, expected_ans);
}

TEST_F(SolverTest, eqn_solve_test_8_zero) {
    Matrix coeff_mat(3, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0});

    Vector constants{0, 0, 0};
    Vector actual_ans = Solver::solve(coeff_mat, constants);
    Vector expected_ans{0, 0, 0};

    EXPECT_EQ(actual_ans, expected_ans);
}


} // namespace astra