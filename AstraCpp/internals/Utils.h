#pragma once

namespace astra::internals::utils {
    void swap(double& a, double& b) {
        double temp = a;
        a = b;
        b = temp;
    }
}
