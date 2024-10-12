#pragma once

#include "Exceptions.h"

namespace astra::internals::mathutils {
    
    const double PI = 3.14159265358979323846;
    const double EPSILON = 1e-6; 

	inline double abs(double x) { return (x < 0) ? -x : x; }

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

    double deg_to_rad(double degree) { return degree * PI / 180.0; }

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

    inline double sin_rad(double angleRadian) {
        angleRadian = fmod(angleRadian, 2 * PI); // normalize the angle
        double sine = 0;
        double term = angleRadian;
        int sign = 1;

        for (int i = 1; i <= 20; i += 2) {
            sine += sign * term;
            sign = -sign;
            term *= (angleRadian * angleRadian) /
                    ((i + 1) * (i + 2)); // calculate the next term
        }
        return sine;
    }


     inline double cos_rad(double angleRadian) {
        angleRadian = fmod(angleRadian, 2 * PI); // Normalize the angle
        double cosine = 1;
        double term = 1;
        int sign = -1;

        for (int i = 2; i <= 20; i += 2) {
            term *= (angleRadian * angleRadian) /
                    ((i - 1) * i); // Calculate the next term
            cosine += sign * term;
            sign = -sign;
        }

        return cosine;
    }

    inline double arcsin_rad(double x) {
        if (x > 1 || x < -1)
            throw astra::internals::exceptions::invalid_argument();
        if (x == 1)
            return PI / 2;
        if (x == -1)
            return -PI / 2;

        double arcsin = 0;
        for (int i = 0; i < 20; i++) {
            arcsin += factorial(2 * i) * pow(x, 2 * i + 1) /
                      (pow(4, i) * pow(factorial(i), 2) * (2 * i + 1));
        }
        return arcsin;
    }

} // namespace astra::internals::mathutils