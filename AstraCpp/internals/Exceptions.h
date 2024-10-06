#pragma once
#include <exception>

namespace astra::internals::exceptions {

class invalid_size : public std::exception {
  public:

    const char* what() const override { return "[ASTRA]  invalid size initialization"; }
};
}  // namespace astra::internals::exceptions
