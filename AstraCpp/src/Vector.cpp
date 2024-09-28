#include "pch.h"
#include "Vector.h"

using namespace astra;

Vector::Vector(int size) {
    this->size = size;
    this->values = new double[size];
}

Vector::~Vector() { 
    delete[] values; 
}