#include <iostream>

#include "../AstraCpp/include/Vector.h"
#include "../AstraCpp/include/Matrix.h"

int main() {
    // ----------VECTOR----------
    double arr[] = {5.5, 6.6, 7.7};
    astra::Vector v1(arr, 3);
    v1.print();

    std::cout << "\n\n";

    astra::Vector v2(3);
    v2 << 3, 5, 7;
    v2.print();

    astra::Vector v3(3);
    v3 = v1 + v2;
    v3.print();

    std::cout << "\n\n";


    // ----------MATRIX----------
    astra::Matrix m(2, 2);

    /*m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;*/

    m << 1, 2,
         4, 5;

    
    std::cout << m(0, 0) << " " << m(0, 1) << "\n"
              << m(1, 0) << " " << m(1, 1) << "\n";

    std::cin.get();

    return 0;
}