#ifndef TEST_OSCILLATOR_HPP
#define TEST_OSCILLATOR_HPP

#include <iostream>
#include "Oscillator.h"

namespace km {
    void testOscillator() {
        std::cout << "Testing Oscillator classes...\n";

        // Creation and test of StdOscillator
        std::unique_ptr<km::StdOscillator> osc1 = std::make_unique<km::StdOscillator>();
        osc1->setOmega([]() { return 1.0; });
		osc1->printOscillator();

        // Creation and test of DoubleOscillator
        std::unique_ptr<km::DoubleOscillator> osc2 = std::make_unique<km::DoubleOscillator>();
        osc2->setOmega([]() { return 1.0; });
		osc2->printOscillator();

        std::cout << "Oscillator tests completed.\n";
    }

};  // namespace km

#endif TEST_OSCILLATOR_HPP

