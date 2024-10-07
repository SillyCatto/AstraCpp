#pragma once
#include <exception>

namespace astra::internals::exceptions {

class invalid_size : public std::exception {
  public:
    const char* what() const override {
        return "[ASTRA]  invalid size initialization";
    }
};

class index_out_of_range : public std::exception {
  public:
    const char* what() const override {
        return "[ASTRA]  index out of range";
    }
};

class init_out_of_range : public std::exception {
  public:
    const char* what() const override {
        return "[ASTRA]  too many elements initialized";
    }
};

class zero_division : public std::exception {
  public:
    const char* what() const override {
        return "[ASTRA]  division by zero";
    }
};

class vector_size_mismatch : public std::exception {
  public:
    const char* what() const override {
        return "[ASTRA]  vector size mismatch for the operation";
    }
};
}  // namespace astra::internals::exceptions
