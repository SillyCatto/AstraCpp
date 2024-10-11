#pragma once

namespace astra::internals::mathutils {

	inline double abs(double x) { return (x < 0) ? -x : x; }

	inline double sqrt(double n) {
        if (n < 0) {
            throw std::invalid_argument("Cannot compute the square root of a negative number");
        }
        if (n == 0) {
            return 0;
        }
            
        double tolerance = 1e-9;
        double guess = n;
        double previous_guess;

        do {
            previous_guess = guess;
            guess = 0.5 * (guess + n / guess); 
        } while (abs(guess - previous_guess) >
                     tolerance); 

        return guess;
     }

} // namespace astra::internals::mathutils