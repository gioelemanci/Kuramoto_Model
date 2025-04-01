#ifndef COUPLINGTYPES_H
#define COUPLINGTYPES_H

#include <cmath>

namespace km {
// Sinusoidal coupling function
    inline double sinusoidalCoupling(double phase_i, double phase_j) {
        return std::sin(phase_j - phase_i);
    }

// Cosinusoidal coupling function
    inline double cosinusoidalCoupling(double phase_i, double phase_j) {
        return std::cos(phase_j - phase_i);
    }

// Linear coupling function
    inline double linearCoupling(double phase_i, double phase_j) {
        return (phase_j - phase_i);
    }

// Exponential coupling function
	inline double exponentialCoupling(double phase_i, double phase_j) {
		return std::exp(phase_j - phase_i);
	}


}; // namespace km

#endif COUPLINGTYPES_H
