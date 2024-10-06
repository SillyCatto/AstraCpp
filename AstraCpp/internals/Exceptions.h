#pragma once
#include <exception>
#include <string>

namespace astra::internals::exceptions {

class invalid_size : public std::exception {
  private:
    std::string msg;

  public:
    invalid_size(const std::string& type) {
        msg = "[ASTRA] invalid size for " + type +
                  " initialization";
    }

    const char* what() const override { return msg.c_str(); }
};
}  // namespace astra::internals::exceptions
