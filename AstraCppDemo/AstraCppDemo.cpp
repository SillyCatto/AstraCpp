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

    return 0;
}