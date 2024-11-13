#pragma once
#include "Matrix.h"

namespace astra {
class Decomposer {
  public:
    struct PLUResult {
        Matrix P;
        Matrix L;
        Matrix U;
        int swaps;

        PLUResult(int size) : P(size, size), L(size, size), U(size, size), swaps(0) {}

        PLUResult(const Matrix& p, const Matrix& l, const Matrix& u, int s)
            : P(p), L(l), U(u), swaps(s) {}
    };

    static PLUResult palu(Matrix A);
};

} // namespace astra
