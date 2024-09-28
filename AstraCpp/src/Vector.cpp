#include "pch.h"
#include "Vector.h"
#include <stdexcept>
#include <iostream>

using namespace astra;

Vector::Vector(int size) {
    if (size < 0) {
        this->size = 0;
        this->values = nullptr;
    }
    else {
    this->size = size;
    this->values = new double[size];
    }
}

Vector::Vector(const double values[]) {
    this->size = size;

    if (size < 0) {
        this->size = 0;
        this->values = nullptr;
    }
    else {
        this->values = new double[size];
        for (int i = 0; i < size; i++) {
            this->values[i] = values[i];
        }
    }
}

Vector::~Vector() { 
    delete[] values; 
}

int Vector::getSize() const { 
    return size; 
}

void Vector::print() const {
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << values[i];
        if (i < size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
