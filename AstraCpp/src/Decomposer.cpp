#include "pch.h"

#include "../include/Matrix.h"
#include "../internals/Exceptions.h"
#include "../include/Decomposer.h"
#include "../internals/MathUtils.h"

namespace astra {

Decomposer::PLUResult Decomposer::palu(Matrix A) {
    int m = A.num_row();

    // matrix is not square
    if (m != A.num_col()) {
        throw astra::internals::exceptions::non_square_matrix();
    }

    Matrix P = Matrix::identity(m);
    Matrix L = Matrix::identity(m);
    Matrix U = A;
    int swaps = 0;

    for (int x = 0; x < m; x++) {
        int pivot_row = x;

        // finding the largest value in the column and selecting it as the pivot
        for (int y = x + 1; y < m; y++) {
            if (internals::mathutils::abs(U(y, x)) >
                internals::mathutils::abs(U(pivot_row, x))) {
                pivot_row = y;
            }
        }

        if (internals::mathutils::nearly_equal(U(pivot_row, x), 0.0)) {
            // all values in the column are zero so we need to skip this column
            continue;
        }

        if (pivot_row != x) {
            // pivot is not in the diagonal so we need to
            // swap rows
            U.row_swap(x, pivot_row); // swaping U
            P.row_swap(x, pivot_row); // swaping P
            L.partial_row_swap(x, pivot_row, x); // partial swapping L till diagonal
            swaps++;
        }

        // eliminate entries below the pivot
        for (int y = x + 1; y < m; y++) {
            double current_val = U(y, x);

            if (internals::mathutils::nearly_equal(current_val, 0.0)) {
                continue; // it is already eliminated
            }

            double pivot = U(x, x);
            double pivot_factor = current_val / pivot;

            U(y, x) = 0; // eliminated

            // update rest of the values in the row
            for (int i = x + 1; i < m; i++) {
                // r2 = r2 - f * r1  (where f = current_val / pivot )

                U(y, i) = U(y, i) - pivot_factor * U(x, i);

                if (internals::mathutils::nearly_equal(U(y, i), 0.0)) {
                    U(y, i) = 0;
                }
            }

            // put the pivot factor in appropriate position of L
            L(y, x) = pivot_factor;
        }
    }

    return PLUResult(P, L, U, swaps);
}
} // namespace astra
