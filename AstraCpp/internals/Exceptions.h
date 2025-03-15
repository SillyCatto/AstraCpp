#pragma once
#include <exception>

namespace astra::internals::exceptions {

class invalid_size : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  invalid size initialization";
    }
};

class index_out_of_range : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  index out of range";
    }
};

class init_out_of_range : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  too many elements initialized";
    }
};

class zero_division : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  division by zero";
    }
};

class vector_size_mismatch : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  vector size mismatch for the operation";
    }
};

class cross_product_size_error : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  cross product is defined for 3D vectors only";
    }
};

class null_vector : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  the vector is null";
    }
};

class matrix_size_mismatch : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  matrix size mismatch for the operation";
    }
};

class non_square_matrix : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  given matrix is not a sqaure matrix for the operation";
    }
};

class matrix_join_size_mismatch : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  cannot join matrices with different number of rows";
    }
};

class invalid_argument : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  invalid argument provided";
    }
};

class matrix_multiplication_size_mismatch : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  matrix's column number and other matrix's row number should be same";
    }
};

class variable_and_value_number_mismatch : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  number of variables and number of values should be same for solver";
    }
};

class singular_matrix : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  singular matrix provided for the operation";
    }
};

class matrix_not_lower_triangular : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  matrix is not lower triangular for the operation";
    }
};

class matrix_not_upper_triangular : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  matrix is not upper triangular for the operation";
    }
};

class no_solution : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  The system of linear equations has no solution";
    }
};

class infinite_solutions : public std::exception {
  public:
    const char* what() const noexcept override {
        return "[ASTRA]  The system of linear equations has infinite solutions";
    }
};

}  // namespace astra::internals::exceptions
