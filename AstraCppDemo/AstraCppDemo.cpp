#include <iostream>

#include "../AstraCpp/include/Vector.h"
#include "../AstraCpp/include/Matrix.h"

int main() {
    // ----------VECTOR----------
    double arr[] = {1, 0, 0};
    astra::Vector v1(3, arr);

    astra::Vector v2(3);
    v2 << 0, 1, 0;

    astra::Vector v3(3);


    std::cout << astra::Vector::angle_deg(v1, v2) << "\n";

    v3 = v1 / 3;
    std::cout << v3 << "\n";

    std::cout << "\n\n";

    double values1[] = {3, 4, 5};
    double values2[] = {1, 2, 3};

    astra::Vector vec1(3, values1);
    astra::Vector vec2(3, values2);

    astra::Vector vec3(3);
    vec3 << 1 << 2 << 3;

    std::cout << "vec1: " << vec1 << "\n"
              << "vec2: " << vec2 << "\n"
              << "vec3: " << vec3 << "\n"; 

    astra::Vector additionResult = vec1 + vec2;
    std::cout << "Addition (vec1 + vec2): " << additionResult << "\n";

    astra::Vector subtractionResult = vec1 - vec2;
    std::cout << "Subtraction (vec1 - vec2): " << subtractionResult << "\n";

    astra::Vector scalarMultiplicationResult = vec1 * 2.0;
    std::cout << "Scalar Multiplication (vec1 * 2): "
              << scalarMultiplicationResult << "\n";

    astra::Vector scalarDivisionResult = vec1 / 2.0;
    std::cout << "Scalar Division (vec1 / 2): " << scalarDivisionResult << "\n";

    astra::Vector crossProductResult = vec1 ^ vec2;
    std::cout << "Cross Product (vec1 ^ vec2): " << crossProductResult << "\n";

    double magnitudeVec1 = vec1.magnitude();
    std::cout << "Magnitude of vec1: " << magnitudeVec1 << "\n";

    astra::Vector normalizedVec1 = vec1.normalize();
    std::cout << "Normalization of vec1: " << normalizedVec1 << "\n";

    double angleRad = astra::Vector::angle(vec1, vec2);
    std::cout << "Angle between vec1 and vec2 (radians): " << angleRad << "\n";

    double angleDeg = astra::Vector::angle_deg(vec1, vec2);
    std::cout << "Angle between vec1 and vec2 (degrees): " << angleDeg << "\n";

    std::cout << "Sum of vec1: " << vec1.sum() << "\n";
    std::cout << "Average of vec1: " << vec1.avg() << "\n";
    std::cout << "Min of vec1: " << vec1.min() << "\n";
    std::cout << "Max of vec1: " << vec1.max() << "\n";

    std::cout << "vec1 == vec2? " << (vec1 == vec2 ? "Yes" : "No") << "\n";

    astra::Vector vec4(3);
    vec4 << 5, 6, 7; 
    std::cout << "vec4 initialized with << and , operators: " << vec4 << "\n";

    // ----------MATRIX----------
    astra::Matrix m(3, 3);

    /*m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;*/

    m << 12.34,   2, 7,
             4, 5.5, 9;

    m.print();

    std::cin.get();

    astra::Matrix matA(2, 2);
    matA << 1.0 << 2.0 << 3.0 << 4.0;
    std::cout << "Matrix A:\n" << matA << "\n";

    double valuesB[] = {5.0, 6.0, 7.0, 8.0};
    astra::Matrix matB(2, 2, valuesB);
    std::cout << "Matrix B:\n" << matB << "\n";

    astra::Matrix matC = matA + matB;
    std::cout << "Matrix A + Matrix B:\n" << matC << "\n";

    astra::Matrix matD = matA - matB;
    std::cout << "Matrix A - Matrix B:\n" << matD << "\n";

    astra::Matrix matE = matA * 2.0;
    std::cout << "Matrix A * 2.0:\n" << matE << "\n";

    astra::Matrix matF = 3.0 * matB;
    std::cout << "3.0 * Matrix B:\n" << matF << "\n";

    astra::Matrix matG = matB / 2.0;
    std::cout << "Matrix B / 2.0:\n" << matG << "\n";

    std::cout << "Element at (0, 1) in Matrix A: " << matA(0, 1) << "\n";

    std::cout << "Matrix A == Matrix A: " << ( matA == matA ? "true" : "false" )
              << "\n";

    astra::Matrix matH = matA;
    std::cout << "Assigned Matrix H from Matrix A:\n" << matH << "\n";

    return 0;
}