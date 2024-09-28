#include "pch.h"
#include "Vector.h"
#include <stdexcept>

using namespace astra;

Vector::Vector(int size) {
    if (size < 0) {
        throw std::invalid_argument("Size must be non-negative");
    }
    this->size = size;
    this->values = new double[size];
}

Vector::~Vector() { 
    delete[] values; 
}

int Vector::getSize() const { 
    return size; 
}
