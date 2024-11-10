#pragma once
#include "Matrix.h"

namespace astra {
class Decomposer {
  public:
    struct PLUResult {
        Matrix P;
        Matrix L;
        Matrix U;

        PLUResult(const Matrix& p, const Matrix& l, const Matrix& u)
            : P(p), L(l), U(u) {}
    };

    static PLUResult palu(Matrix A);
};

} // namespace astra
