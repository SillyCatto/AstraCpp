#pragma once

namespace astra::internals::utils {
    inline void swap(double& a, double& b) {
        double temp = a;
        a = b;
        b = temp;
    }
}
