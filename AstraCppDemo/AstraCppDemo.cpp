#include <iostream>

#include "../AstraCpp/include/Vector.h"
#include "../AstraCpp/include/Matrix.h"

int main() {
    double arr[] = {5.5, 6.6, 7.7};

    astra::Vector vec(arr, 3);

    vec.print();

    std::cin.get();

    return 0;
}