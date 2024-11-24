#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Decomposer.h"

// TODO: implement solver using LU

// Ax = b
// A = LU
// LUx = b
// let Ux = y
// Ly = b
// solve by forward and backward substitution

// next step: implemet functions for forward and backward sub

namespace astra {
class Solver {
  private:

  public:
    static Vector forward_sub(Matrix L, Vector b);
    static Vector backward_sub(Matrix U, Vector b);
    static Vector plu_solve(Matrix A, Vector b);
};

}
