#include "pch.h"
#include "Vector.h"
#include "Exceptions.h"
#include "MathUtils.h"

#include <cmath>
#include <iostream>


using namespace astra;

Vector::Vector(int size) : size(size), current_index(0), values(nullptr) {
    if (size <= 0) {
        throw astra::internals::exceptions::invalid_size();
    }
    this->values = new double[size];

    for (int i = 0; i < size; ++i) {
        this->values[i] = 0;
    }
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

Vector& Vector::operator<<(double val) {
    if (current_index < size) {
        values[current_index++] = val;
    }
    else {
        throw astra::internals::exceptions::init_out_of_range();
    }
    return *this;
}

Vector &Vector::operator,(double val) { return (*this << val); }

double Vector::operator*(const Vector& other) const {
    if (this->size != other.size) {
        throw astra::internals::exceptions::vector_size_mismatch();
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
        throw astra::internals::exceptions::zero_division();
    }
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.values[i] = this->values[i] / scalar;
    }
    return result;
}

Vector Vector::operator+(const Vector& other) const {
    if (this->size != other.size) {
        throw astra::internals::exceptions::vector_size_mismatch();
    }

    Vector result(size);

    for (int i = 0; i < size; ++i) {
        result.values[i] = this->values[i] + other.values[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (this->size != other.size) {
        throw astra::internals::exceptions::vector_size_mismatch();
    }
    Vector result(size);

    for (int i = 0; i < size; ++i) {
        result.values[i] = this->values[i] - other.values[i];
    }
    return result;
}

double Vector::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw astra::internals::exceptions::index_out_of_range();
    }
    return values[index];
}

Vector Vector::operator^(const Vector& other) const {
    if (this->size != 3 || other.size != 3) {
        throw astra::internals::exceptions::cross_product_size_error();
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
        if (astra::internals::mathutils::abs(this->values[i] - other.values[i]) >
            1e-8) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const { 
    return !(*this == other); 
}

double Vector::magnitude() const {
    double sum_of_squares = 0.0;
    for (int i = 0; i < size; ++i) {
        sum_of_squares += values[i] * values[i];
    }
    return astra::internals::mathutils::sqrt(sum_of_squares);
}

double astra::Vector::sum() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += values[i];
    }
    return sum;
}

double Vector::avg() const { 
	return sum() / size; 
}

double astra::Vector::min() const {
    double min = values[0];
    for (int i = 1; i < size; ++i) {
        if (values[i] < min) {
            min = values[i];
        }
    }
    return min;
}

double astra::Vector::max() const {
    double max = values[0];
    for (int i = 1; i < size; ++i) {
        if (values[i] > max) {
            max = values[i];
        }
    }
    return max;
}

Vector astra::Vector::normalize() const { 
	double mag = magnitude();
    if (mag == 0) {
        throw astra::internals::exceptions::zero_division();
    }
    return *this / mag;
}

std::ostream& astra::operator<<(std::ostream& ost, const Vector& v) {
    ost << "[";
    for (int i = 0; i < v.size; ++i) {
        ost << v.values[i];
        if (i < v.size - 1) {
            ost << ", ";
        }
    }
    ost << "]";
    return ost;
}


double Vector::angle(const Vector& v1, const Vector& v2) {
    if (v1.get_size() != v2.get_size()) {
        throw astra::internals::exceptions::vector_size_mismatch();
    }

    double mag_v1 = v1.magnitude();
    double mag_v2 = v2.magnitude();

    if (mag_v1 == 0 || mag_v2 == 0) {
        throw astra::internals::exceptions::null_vector();
    }

    double dot_product = v1 * v2;

    double cos_theta = dot_product / (mag_v1 * mag_v2);

    cos_theta = astra::internals::mathutils::clamp(cos_theta, -1.0, 1.0);

    double angle_radians = std::acos(cos_theta);

    return angle_radians;
}

