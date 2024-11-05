#pragma once

#include "Exceptions.h"

namespace astra::internals::mathutils {
    
    const double PI = 3.14159265358979323846;
    const double EPSILON = 1e-6; 

	inline double abs(double x) { return (x < 0) ? -x : x; }

    inline double fmax(double a, double b) { return (a > b) ? a : b; }

    inline double fmin(double a, double b) { return (a < b) ? a : b; }

    inline double clamp(double value, double min, double max) {
        return fmax(min, fmin(value, max));
    }

	inline double sqrt(double n) {
        if (n < 0) {
            throw astra::internals::exceptions::invalid_argument();
        }
        if (n == 0) {
            return 0;
        }
            
        double tolerance = EPSILON;
        double guess = n;
        double previous_guess;

        do {
            previous_guess = guess;
            guess = 0.5 * (guess + n / guess); 
        } while (abs(guess - previous_guess) >
                     tolerance); 

        return guess;
     }

    inline double deg_to_rad(double deg) { return deg * PI / 180.0; }
    inline double rad_to_deg(double rad) { return rad * (180.0 / PI); }

    inline unsigned long long factorial(int n) {
         unsigned long long fact = 1;
         for (int i = 2; i <= n; ++i) {
             fact *= i;
         }
         return fact;
     }

    inline double pow(double base, int exponent) {
         if (exponent == 0) {
             return 1.0;
         }

         if (base == 0.0 && exponent < 0) {
             throw astra ::internals::exceptions::zero_division();
         }

         double res = 1.0;
         int abs_exp = (exponent > 0) ? exponent : -exponent;

         while (abs_exp > 0) {
             if (abs_exp % 2 == 1) {
                 res *= base;
             }

             base *= base;
             abs_exp /= 2;
         }

         return (exponent < 0) ? 1.0 / res : res;
     }

    inline double trunc(double x) {
         if (x > 0) {
            return static_cast<int>(x);
         }
         else if (x < 0) {
             return static_cast<int>(x);
         }
         else {
             return 0.0;
         }
    }

    inline double fmod(double x, double y) {
        if (y == 0.0) {
            throw astra::internals::exceptions::zero_division();
        }

        double quotient = trunc(x / y);

        double res = x - quotient * y;
        return res;
    }

} // namespace astra::internals::mathutils