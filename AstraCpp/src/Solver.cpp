#include "pch.h"

#include "Vector.h"
#include "Matrix.h"
#include "Solver.h"

using namespace astra;

Vector Solver::forward_sub(Matrix L, Vector b) { 
	int m = b.get_size();
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
