#pragma once
#include <exception>

namespace astra::internals::exceptions {

class invalid_vector_size : public std::exception {

  public:
    const char* what() const noexcept override {
        return "[ERROR]  vector size must be positive";
    }
};
}  // namespace astra::internals::exceptions
