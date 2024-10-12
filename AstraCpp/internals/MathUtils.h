#pragma once
#include "Exceptions.h"

namespace astra::internals::mathutils {
    
    const double PI = 3.14159265358979323846;
    const double EPSILON = 1e-9; 

	inline double abs(double x) { return (x < 0) ? -x : x; }

	inline double sqrt(double n) {
        if (n < 0) {
            throw astra::internals::exceptions::invalid_argument();
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

    inline unsigned long long factorial(int n) {
         unsigned long long fact = 1;
         for (int i = 2; i <= n; ++i) {
             fact *= i;
         }
         return fact;
     }

    inline double sin(double x) {
         double term = x;      
         double result = term; 
         int sign = -1;        

         for (int i = 3; i <= 19; i += 2) {
             term = (x * x * x) / factorial(i); 
             result += sign * term;             
             sign *= -1; 
         }
         return result;
     }

     inline double cos(double x) {
        double term = 1;      
        double result = term; 
        int sign = -1;        

        for (int i = 2; i <= 18; i += 2) {
            term = (x * x) / factorial(i); 
            result += sign * term;         
            sign *= -1; 
        }
        return result;
     }

    inline double acos(double x) {
         if (x < -1.0 || x > 1.0) {
            throw astra::internals::exceptions::invalid_argument();
         }

         if (astra::internals::mathutils::abs(x - 1.0) < EPSILON)
             return 0.0; 
         if (astra::internals::mathutils::abs(x + 1.0) < EPSILON)
             return PI; 

         double guess = PI / 4;
         double fx, dfx;

         while (true) {
             fx = cos(guess) - x;

             dfx = -sin(guess);

             double next_guess = guess - fx / dfx;

             if (astra::internals::mathutils::abs(next_guess - guess) <
                 EPSILON) {
                 break;
             }

             guess = next_guess;
         }

         return guess;
     }

} // namespace astra::internals::mathutils