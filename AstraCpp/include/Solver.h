#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "Matrix.h"
#include "Vector.h"
#include "Decomposer.h"

// Ax = b
// A = LU
// LUx = b
// let Ux = y
// Ly = b
// solve by forward and backward substitution

namespace astra {
class Solver {
  private:
  public:
    static Vector forward_sub(Matrix L, Vector b);
    static Vector backward_sub(Matrix U, Vector b);
    static Vector solve(Matrix A, Vector b);
};
} // namespace astra
#endif // !__SOLVER_H__
