#include <iostream>

#include "../AstraCpp/include/Vector.h"
#include "../AstraCpp/include/Matrix.h"

int main() {
    double arr[] = {5.5, 6.6, 7.7};

    astra::Vector vec(arr, 3);

    vec.print();

    std::cout << "\n\n";

    astra::Matrix m(2, 2);

    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;
    
    std::cout << m(0, 0) << " " << m(0, 1) << "\n"
              << m(1, 0) << " " << m(1, 1) << "\n";

    std::cin.get();

    return 0;
}