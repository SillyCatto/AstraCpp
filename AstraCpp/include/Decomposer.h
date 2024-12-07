/**
 * @file Decomposer.h
 * @brief Declaration of the Decomposer class, which provides functions and utilities
 * for matrix decomposition
 */

#ifndef __DECOMPOSER_H__
#define __DECOMPOSER_H__

#include "Matrix.h"

namespace astra {

/**
 * @class Decomposer
 * @brief A utility class for performing matrix decompositions such as PA=LU.
 */
class Decomposer {
  public:
    /**
     * @struct PLUResult
     * @brief Stores the result of the PA=LU decomposition.
     *
     * Contains the permutation matrix (P), lower triangular matrix (L),
     * upper triangular matrix (U), and the number of row swaps (swaps).
     */
    struct PLUResult {
        Matrix P;
        Matrix L;
        Matrix U;
        int swaps;

        /**
         * @brief Constructs an empty PLUResult with identity matrices.
         * @param size The size of the square matrices P, L, and U.
         */
        PLUResult(int size) : P(size, size), L(size, size), U(size, size), swaps(0) {}

        /**
         * @brief Constructs a PLUResult with specified matrices and swaps.
         * @param p The permutation matrix.
         * @param l The lower triangular matrix.
         * @param u The upper triangular matrix.
         * @param s The number of row swaps performed.
         */
        PLUResult(const Matrix& p, const Matrix& l, const Matrix& u, int s)
            : P(p), L(l), U(u), swaps(s) {}
    };

    /**
     * @brief Performs PA=LU decomposition on a square matrix.
     *
     * Decomposes a square matrix A into three matrices: P (permutation matrix),
     * L (lower triangular matrix), and U (upper triangular matrix), such that
     * P * A = L * U. It also counts the number of row swaps needed during
     * the decomposition.
     *
     * @param A The square matrix to decompose.
     * @return PLUResult The decomposition result containing P, L, U, and swaps.
     * @throws astra::internals::exceptions::non_square_matrix if A is not
     * square.
     */
    static PLUResult palu(Matrix A);
};
} // namespace astra
#endif // !__DECOMPOSER_H__
