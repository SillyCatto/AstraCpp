#include <iostream>

#include "../AstraCpp/include/Vector.h"
#include "../AstraCpp/include/Matrix.h"
#include "../AstraCpp/include/Decomposer.h"

int main() {
    // ----------VECTOR----------

    //std::cout << "VECTOR\n";
    //std::cout << "------\n\n";

    //double values1[] = {3, 4, 5};
    //double values2[] = {11, 13, 15};
    //astra::Vector vec1(3, values1);

    ////astra::Vector vec2(3);
    //astra::Vector vec2(3, values2);
    ////std::cin >> vec2;

    //astra::Vector vec3{1, 2, 3, 4};

    //std::cout << "vec1: " << vec1 << "\n"
    //          << "vec2: " << vec2 << "\n"
    //          << "vec3: " << vec3 << "\n\n"; 

    //astra::Vector additionResult = vec1 + vec2;
    //std::cout << "Addition (vec1 + vec2): " << additionResult << "\n";

    //astra::Vector subtractionResult = vec1 - vec2;
    //std::cout << "Subtraction (vec1 - vec2): " << subtractionResult << "\n";

    //astra::Vector scalarMultiplicationResult = vec1 * 2.0;
    //std::cout << "Scalar Multiplication (vec1 * 2): "
    //          << scalarMultiplicationResult << "\n";

    //astra::Vector scalarDivisionResult = vec1 / 2.0;
    //std::cout << "Scalar Division (vec1 / 2): " << scalarDivisionResult << "\n\n";

    //double dotProductResult = vec1 * vec2;
    //std::cout << "Dot Product (vec1 * vec2): " << dotProductResult<< "\n";

    //astra::Vector crossProductResult = vec1 ^ vec2;
    //std::cout << "Cross Product (vec1 ^ vec2): " << crossProductResult << "\n\n";

    //double magnitudeVec1 = vec1.magnitude();
    //std::cout << "Magnitude of vec1: " << magnitudeVec1 << "\n";

    //astra::Vector normalizedVec1 = vec1.normalize();
    //std::cout << "Normalization of vec1: " << normalizedVec1 << "\n\n";

    //double angleRad = astra::Vector::angle(vec1, vec2);
    //std::cout << "Angle between vec1 and vec2 (radians): " << angleRad << "\n";

    //double angleDeg = astra::Vector::angle_deg(vec1, vec2);
    //std::cout << "Angle between vec1 and vec2 (degrees): " << angleDeg << "\n\n";

    //std::cout << "Sum of vec1: " << vec1.sum() << "\n";
    //std::cout << "Average of vec1: " << vec1.avg() << "\n";
    //std::cout << "Min of vec1: " << vec1.min() << "\n";
    //std::cout << "Max of vec1: " << vec1.max() << "\n";

    //std::cout << "vec1 == vec2? " << (vec1 == vec2 ? "true" : "false") << "\n\n";


    // ----------MATRIX----------

    std::cout << "MATRIX\n";
    std::cout << "------\n\n";

    //astra::Matrix matA(2, 2);
    ////std::cin >> matA;

    //matA << 1.0, 2.0, 3.0, 4.0;

    //std::cout << "Matrix A:\n" << matA << "\n";

    //astra::Matrix matB(2, 2, 
    //    {
    //        5.0, 6.0, 
    //        7.0, 8.0
    //    }
    //);

    //std::cout << "Matrix B:\n" << matB << "\n";

    //matB.row_swap(0, 1);

    //std::cout << "Matrix B after swap:\n" << matB << "\n";

    //astra::Matrix matC = matA + matB;
    //std::cout << "Matrix A + Matrix B:\n" << matC << "\n";

    //astra::Matrix matD = matA - matB;
    //std::cout << "Matrix A - Matrix B:\n" << matD << "\n";

    //astra::Matrix matE = matA * 2.0;
    //std::cout << "Matrix A * 2.0:\n" << matE << "\n";

    //astra::Matrix matF = 3.0 * matB;
    //std::cout << "3.0 * Matrix B:\n" << matF << "\n";

    //astra::Matrix matG = matB / 2.0;
    //std::cout << "Matrix B / 2.0:\n" << matG << "\n";

    //std::cout << "Element at (0, 1) in Matrix A: " << matA(0, 1) << "\n";

    //std::cout << "Matrix A == Matrix A: " << ( matA == matA ? "true" : "false" )
    //          << "\n";

    //astra::Matrix matH = matA;
    //std::cout << "Assigned Matrix H from Matrix A:\n" << matH << "\n\n";

    astra::Matrix mat1(3, 3, 
        {
            4, 2, 0,
            1, 3, 5,
            0, 2, 1
        }
    );

    auto plu_res = astra::Decomposer::palu(mat1);

    std::cout << "P:\n";
    std::cout << plu_res.P;

    std::cout << "L:\n";
    std::cout << plu_res.L;

    std::cout << "U:\n";
    std::cout << plu_res.U;

    std::cout << "\nDet(mat1): " << mat1.det() << "\n";

    std::cin.get();

    return 0;
}