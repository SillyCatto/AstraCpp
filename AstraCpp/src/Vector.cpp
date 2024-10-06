#include "pch.h"
#include "Vector.h"
#include <stdexcept>
#include <iostream>

#include "Exceptions.h"

using namespace astra;


Vector::Vector(int size) : size(size), current_index(0), values(nullptr) {
    if (size <= 0) {
        throw astra::internals::exceptions::invalid_size();
    }
    this->values = new double[size];
}

Vector::Vector(const double values[], int size)
    : size(size), current_index(size), values(nullptr) {
    if (size <= 0) {
        throw astra::internals::exceptions::invalid_size();
    }
    this->values = new double[size];

    for (int i = 0; i < size; ++i) {
        this->values[i] = values[i];
    }
}

Vector::Vector(const Vector& other)
    : size(other.size), current_index(other.current_index), values(nullptr) {

    if (size > 0) {
        this->values = new double[size];
        for (int i = 0; i < size; ++i) {
            this->values[i] = other.values[i];
        }
    }
}

Vector::~Vector() { 
    delete[] values;
    values = nullptr;
}

int Vector::get_size() const { 
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

Vector& Vector::operator<<(double val) {
    if (current_index < size) {
        values[current_index++] = val;
    }
    else {
        throw std::out_of_range("[ERROR]  too many elements for vector");
    }
    return *this;
}

Vector &Vector::operator,(double val) { return (*this << val); }

double Vector::operator*(const Vector& other) const {
    if (this->size != other.size) {
        throw std::invalid_argument(
            "[ERROR]  vectors must be same size for dot product");
    }
    double result = 0;
    for (int i = 0; i < size; ++i) {
        result += this->values[i] * other.values[i];
    }
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.values[i] = this->values[i] * scalar;
    }
    return result;
}

Vector Vector::operator/(double scalar) const {
    if (scalar == 0) {
        throw std::invalid_argument("[ERROR]  division by zero");
    }
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.values[i] = this->values[i] / scalar;
    }
    return result;
}

Vector Vector::operator+(const Vector& other) const {
    if (this->size != other.size) {
        throw std::invalid_argument(
            "[ERROR]  vectors must be same size for addition");
    }

    Vector result(size);

    for (int i = 0; i < size; ++i) {
        result.values[i] = this->values[i] + other.values[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (this->size != other.size) {
        throw std::invalid_argument("[ERROR]  vectors must be same size for subtraction");
    }
    Vector result(size);

    for (int i = 0; i < size; ++i) {
        result.values[i] = this->values[i] - other.values[i];
    }
    return result;
}

double Vector::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("[ERROR]  vector index out of range");
    }
    return values[index];
}

Vector Vector::operator^(const Vector& other) const {
    if (this->size != 3 || other.size != 3) {
        throw std::invalid_argument(
            "[ERROR]  cross product is defined for 3D vectors only");
    }
    Vector result(3);
    result.values[0] =
        this->values[1] * other.values[2] - this->values[2] * other.values[1];
    result.values[1] =
        this->values[2] * other.values[0] - this->values[0] * other.values[2];
    result.values[2] =
        this->values[0] * other.values[1] - this->values[1] * other.values[0];
    return result;
}

Vector& Vector::operator=(const Vector& other) {  
    if (this == &other) {
        return *this;
    }

    delete[] values;

    size = other.size;
    values = new double[size];
    for (int i = 0; i < size; ++i) {
        values[i] = other.values[i];
    }

    return *this;
}

bool Vector::operator==(const Vector& other) const {
    if (this->size != other.size) {
        return false;
    }
    for (int i = 0; i < size; ++i) {
        if (std::abs(this->values[i] - other.values[i]) > 1e-9) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const { 
    return !(*this == other); 
}