#include "pch.h"

#include "Vector.h"
#include "Matrix.h"
#include "Solver.h"
#include "Exceptions.h"
#include "Decomposer.h"

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
    if (!A.is_square()) {
        throw internals::exceptions::non_square_matrix();
    }
    else if (A.num_col() != b.get_size()) {
        throw internals::exceptions::variable_and_value_number_mismatch();
    }



    int m = A.num_col();
    Vector y(m);
    Vector x(m);

    auto plu_res = Decomposer::palu(A);
    b = plu_res.P * b;

    y = forward_sub(plu_res.L, b);
    x = backward_sub(plu_res.U, y);
    return x;
}
} // namespace astra
