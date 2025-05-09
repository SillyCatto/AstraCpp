#include "pch.h"

#include "../include/Matrix.h"
#include "../internals/Exceptions.h"
#include "../include/Decomposer.h"
#include "../include/Solver.h"
#include "../include/Vector.h"

namespace astra {

Vector Solver::forward_sub(Matrix L, Vector b) {
    int m = b.get_size();

    if (L.num_col() != m) {
        throw astra::internals::exceptions::
            variable_and_value_number_mismatch();
    }
    else if (!L.is_lower_triangular()) {
        throw astra::internals::exceptions::matrix_not_lower_triangular();
    }

    Vector x(m);

    for (int v = 0; v < m; v++) {
        if (L(v, v) == 0) {
            // the diagonal is zero
            x[v] = 0;
            continue;
        }

        double value = b[v];
        for (int i = 0; i < v; i++) {
            value -= L(v, i) * x[i];
        }
        x[v] = value / L(v, v);
    }
    return x;
}

Vector astra::Solver::backward_sub(Matrix U, Vector b) {
    int m = b.get_size();

    if (U.num_col() != m) {
        throw astra::internals::exceptions::
            variable_and_value_number_mismatch();
    }
    else if (!U.is_upper_triangular()) {
        throw astra::internals::exceptions::matrix_not_upper_triangular();
    }

    Vector x(m);

    for (int v = m - 1; v > -1; v--) {
        if (U(v, v) == 0) {
            x[v] = 0;
            continue;
        }

        double value = b[v];
        for (int i = v + 1; i < m; i++) {
            value -= U(v, i) * x[i];
        }
        x[v] = value / U(v, v);
    }
    return x;
}

Vector Solver::solve(Matrix A, Vector b) {
    // Unique Solution    : rank(A) = rank([A | b]) = n 
    // Infinite Solutions : rank(A) = rank([A | b]) < n 
    // No Solution        : rank(A) < rank([A | b])

    if (A.num_col() != b.get_size()) {
        throw internals::exceptions::variable_and_value_number_mismatch();
    }

    // make the vector a single col matrix
    Matrix b_mat(b.get_size(), 1);
    for (int i = 0; i < b.get_size(); i++) {
        b_mat(i, 0) = b[i];
    }

    // create A|b
    Matrix A_aug_b = A;
    A_aug_b.join(b_mat);

    // get the ranks and var no.
    int rank_A = A.rank();
    int rank_A_aug_b = A_aug_b.rank();
    int num_variables = A.num_col();

    // check for no solution
    if (rank_A < rank_A_aug_b) {
        throw internals::exceptions::no_solution();
    }

    // check for infinite solutions
    if (rank_A == rank_A_aug_b && rank_A < num_variables) {
        throw internals::exceptions::infinite_solutions();
    }

    // unique soln
    auto plu_res = Decomposer::palu(A);
    b = plu_res.P * b;

    Vector y = forward_sub(plu_res.L, b);
    Vector x = backward_sub(plu_res.U, y);
    return x;
}
} // namespace astra
