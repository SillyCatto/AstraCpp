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
    Matrix coeff_mat(3, 3, {1, 2, 3, 
                            4, 5, 6, 
                            7, 8, 10}
    );

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
    Matrix coeff_mat(3, 3, {0, 0, 0, 
                            0, 0, 0, 
                            0, 0, 0}
    );

    Vector constants{0, 0, 0};
    Vector actual_ans = Solver::solve(coeff_mat, constants);
    Vector expected_ans{0, 0, 0};

    EXPECT_EQ(actual_ans, expected_ans);
}

TEST_F(SolverTest, eqn_solve_test_forward_sub_1) {
    Matrix L(3, 3, {1, 0, 0, 
                    2, 1, 0, 
                    3, 4, 1}
    );

    Vector b{1, 2, 3};
    Vector actual_ans = Solver::forward_sub(L, b);
    Vector expected_ans{1, 0, 0};

    EXPECT_EQ(actual_ans, expected_ans);
}

TEST_F(SolverTest, eqn_solve_test_forward_sub_2) {
    Matrix L(3, 3, {1, 0, 0, 
                    2, 1, 0, 
                    3, 4, 1}
    );

    Vector b{1, 3, 3};
    Vector actual_ans = Solver::forward_sub(L, b);
    Vector expected_ans{1, 1, -4};

    EXPECT_EQ(actual_ans, expected_ans);
}

TEST_F(SolverTest, eqn_solve_test_forward_sub_3_invalid) {
    Matrix L(3, 3, {1, 0, 0, 
                    2, 1, 0, 
                    3, 4, 1}
    );

    Vector b{1, 3};
    EXPECT_THROW(Solver::forward_sub(L, b),
                 internals::exceptions::variable_and_value_number_mismatch);
}

TEST_F(SolverTest, eqn_solve_test_forward_sub_4_4x4) {
    Matrix L(4, 4, {1, 0, 0, 0, 
                    2, 1, 0, 0, 
                    3, 4, 1, 0,
                    4, 5, 6, 1}
    );

    Vector b{1, 2, 3, 4};
    Vector actual_ans = Solver::forward_sub(L, b);
    Vector expected_ans{1, 0, 0, 0};

    EXPECT_EQ(actual_ans, expected_ans);
}

TEST_F(SolverTest, eqn_solve_test_forward_sub_5_notLower) {
    Matrix L(3, 3, {1, 0, 0, 
                    0, 2, 1, 
                    0, 0, 3}
    );

    Vector b{1, 2, 3};
    EXPECT_THROW(Solver::forward_sub(L, b),
                 internals::exceptions::matrix_not_lower_triangular);
}

TEST_F(SolverTest, eqn_solve_test_backward_sub_1) {
    Matrix U(3, 3, {1, 2, 3, 
                    0, 1, 4, 
                    0, 0, 1}
    );

    Vector b{1, 2, 3};
    Vector actual_ans = Solver::backward_sub(U, b);
    Vector expected_ans{12, -10, 3};

    EXPECT_EQ(actual_ans, expected_ans);
}

TEST_F(SolverTest, eqn_solve_test_backward_sub_2) {
    Matrix U(3, 3, {6, 8, 9, 
                    0, 3, 7, 
                    0, 0, 1}
    );

    Vector b{98, 30, 0};
    Vector actual_ans = Solver::backward_sub(U, b);
    Vector expected_ans{3, 10, 0};

    EXPECT_EQ(actual_ans, expected_ans);
}

TEST_F(SolverTest, eqn_solve_test_backward_sub_3_invalid) {
    Matrix U(3, 3, {1, 2, 3, 
                    0, 1, 4, 
                    0, 0, 1}
    );

    Vector b{1, 3};
    EXPECT_THROW(Solver::backward_sub(U, b),
                 internals::exceptions::variable_and_value_number_mismatch);
}

TEST_F(SolverTest, eqn_solve_test_backward_sub_4_4x4) {
    Matrix U(4, 4, {1, 2, 3, 4, 
                    0, 1, 2, 3, 
                    0, 0, 1, 2, 
                    0, 0, 0, 1}
    );

    Vector b{10, 20, 30, 40};
    Vector actual_ans = Solver::backward_sub(U, b);
    Vector expected_ans{0, 0, -50, 40};

    EXPECT_EQ(actual_ans, expected_ans);
}

TEST_F(SolverTest, eqn_solve_test_backward_sub_5_notUpper) {
    Matrix U(3, 3, {1, 0, 0, 
                    2, 1, 0, 
                    3, 4, 1}
    );

    Vector b{1, 2, 3};
    EXPECT_THROW(Solver::backward_sub(U, b),
                 internals::exceptions::matrix_not_upper_triangular);
}

TEST_F(SolverTest, eqn_solve_test_nearly_singular) {
    Matrix coeff_mat(3, 3, {1, 1, 1, 2, 2.0001, 2, 3, 3, 3.0001});

    Vector constants{3, 6, 9};
    Vector actual_ans = Solver::solve(coeff_mat, constants);
    Vector expected_ans{3, 0, 0};

    EXPECT_EQ(actual_ans, expected_ans);
}


} // namespace astra