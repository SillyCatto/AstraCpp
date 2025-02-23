/**
 * @file Solver.h
 * @brief Declaration of the Solver class, which provides methods for solving
 * linear systems of equations using forward and backward substitution.
 */

#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "Decomposer.h"
#include "Matrix.h"
#include "Vector.h"

// Ax = b
// A = LU
// LUx = b
// let Ux = y
// Ly = b
// solve by forward and backward substitution

namespace astra {

/**
 * @class Solver
 * @brief A utility class for solving linear systems of equations.
 *
 * The Solver class provides static methods for solving systems of equations
 * of the form Ax = b using LU decomposition and forward/backward substitution.
 */
class Solver {
  public:
    /**
     * @brief Solves a lower triangular system using forward substitution.
     *
     * Given a lower triangular matrix L and a right-hand side vector b,
     * this function solves for x in Lx = b using forward substitution.
     *
     * @param L A lower triangular matrix.
     * @param b The right-hand side vector.
     * @return Vector The solution vector x.
     * @throws astra::internals::exceptions::variable_and_value_number_mismatch
     * if the dimensions of L and b do not match.
     * @throws astra::internals::exceptions::matrix_not_lower_triangular
     * if L is not a lower triangular matrix.
     */
    static Vector forward_sub(Matrix L, Vector b);

    /**
     * @brief Solves an upper triangular system using backward substitution.
     *
     * Given an upper triangular matrix U and a right-hand side vector b,
     * this function solves for x in Ux = b using backward substitution.
     *
     * @param U An upper triangular matrix.
     * @param b The right-hand side vector.
     * @return Vector The solution vector x.
     * @throws astra::internals::exceptions::variable_and_value_number_mismatch
     * if the dimensions of U and b do not match.
     * @throws astra::internals::exceptions::matrix_not_upper_triangular
     * if U is not an upper triangular matrix.
     */
    static Vector backward_sub(Matrix U, Vector b);

    /**
     * @brief Solves a linear system Ax = b using LU decomposition.
     *
     * The function first decomposes A into PA = LU using PLU decomposition,
     * then solves for x by performing forward substitution on L and backward
     * substitution on U.
     *
     * @param A A square matrix representing the coefficients of the system.
     * @param b The right-hand side vector.
     * @return Vector The solution vector x.
     * @throws astra::internals::exceptions::non_square_matrix
     * if A is not square.
     * @throws astra::internals::exceptions::variable_and_value_number_mismatch
     * if the dimensions of A and b do not match.
     */
    static Vector solve(Matrix A, Vector b);
};

} // namespace astra

#endif // !__SOLVER_H__
