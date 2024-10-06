#pragma once
#include <exception>

namespace astra::internals::exceptions {

class invalid_size : public std::exception {
  public:

    const char* what() const override { return "[ASTRA]  invalid size initialization"; }
};

class index_out_of_range : public std::exception {
  public:
    const char* what() const override {
        return "[ASTRA]  index out of range";
    }
};
}  // namespace astra::internals::exceptions
