#include "pch.h"

#include "Matrix.h"
#include "Exceptions.h"
#include "Decomposer.h"

using namespace astra;

Decomposer::PLUResult Decomposer::palu(Matrix A) { 
	int m = A.num_row();
    if (m != A.num_col()) {
            throw astra::internals::exceptions::non_sqauare_matrix();
    }

    Matrix P = Matrix::identity(m);
    Matrix L = Matrix::identity(m);
    Matrix U = A;
    int swaps = 0;






    Decomposer::PLUResult res(3);
    return res;
}
