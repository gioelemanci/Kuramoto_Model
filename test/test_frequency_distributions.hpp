#ifndef TEST_FREQUENCY_DISTRIBUTIONS_HPP
#define TEST_FREQUENCY_DISTRIBUTIONS_HPP

#include <iostream>
#include "FrequencyDistributions.hpp"

namespace km {
    void testFrequencyDistributions() {
        std::cout << "Testing Frequency Distributions...\n";

        std::cout << "Uniform Frequency: " << uniformFrequency() << "\n";

        auto normalDist = normalFrequency(1.0, 0.2);
        std::cout << "Normal Frequency: " << normalDist() << "\n";

        auto lorentzianDist = lorentzianFrequency(1.0);
        std::cout << "Lorentzian Frequency: " << lorentzianDist() << "\n";

        auto bimodalDist = bimodalFrequency();
        std::cout << "Bimodal Frequency: " << bimodalDist() << "\n";

        auto exponentialDist = exponentialFrequency(1.0);
        std::cout << "Exponential Frequency: " << exponentialDist() << "\n";

        std::vector<double> customFrequencies = { 0.5, 1.5, 2.5 };
        FrequencyDistributor distributor(customFrequencies);
        std::cout << "Custom Frequency Distribution: "
            << distributor() << " "
            << distributor() << " "
            << distributor() << " "
            << distributor() << "\n";

        std::cout << "Frequency Distributions tests completed.\n";
    }

}; // namespace km

#endif // TEST_FREQUENCY_DISTRIBUTIONS_HPP
