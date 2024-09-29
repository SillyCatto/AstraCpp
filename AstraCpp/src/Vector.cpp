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

Vector::Vector(const double values[], int size) {
    if (size < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }

    this->size = size;
    this->values = new double[size];

    for (int i = 0; i < size; ++i) {
        this->values[i] = values[i];
    }
}

Vector::Vector(const Vector& other) {
    this->size = other.size;
    this->values = new double[size];

    for (int i = 0; i < size; ++i) {
        this->values[i] = other.values[i];
    }

}

Vector::~Vector() { 
    delete[] values; 
}

int Vector::get_size() const { 
    return size; 
}

bool astra::Vector::is_null() const { return (size == 0); }

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

double Vector::operator*(const Vector& other) const {
    if (this->size != other.size) {
        throw std::invalid_argument(
            "Vectors must be of the same size for dot product.");
    }
    double result = 0;
    for (int i = 0; i < size; ++i) {
        result += this->values[i] * other.values[i];
    }
    return result;
}

Vector Vector::operator+(const Vector& other) const {
    if (this->size != other.size) {
        throw std::invalid_argument(
            "Vectors must be of the same size for addition.");
    }
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.values[i] = this->values[i] + other.values[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (this->size != other.size) {
        throw std::invalid_argument("Vectors must be of the same size for subtraction.");
    }
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.values[i] = this->values[i] - other.values[i];
    }
    return result;
}

double Vector::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    return values[index];
}