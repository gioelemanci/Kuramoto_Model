#ifndef TEST_KURAMOTO_HPP
#define TEST_KURAMOTO_HPP

#include <iostream>
#include "Kuramoto.h"
#include "Oscillator.h"

namespace km {
    void testKuramoto() {
        std::cout << "Testing KuramotoModel class...\n";

		// Creation of a KuramotoModel
        KuramotoModel model;
        model.setCouplingStrenght(0.5);

		// Adding oscillators
        std::shared_ptr<StdOscillator> osc1 = std::make_shared<StdOscillator>();
        std::shared_ptr<StdOscillator> osc2 = std::make_shared<StdOscillator>();

        osc1->setTheta(0.0);
        osc2->setTheta(1.0);

        model.addOscillator(osc1);
        model.addOscillator(osc2);

		// Setting the frequency distribution
        model.setFrequencyDistribution([]() { return 1.0; });
        model.setNaturalFrequencies();

		// Printing basic information
        std::cout << "Number of oscillators: " << model.getNumOscillators() << "\n";
        std::cout << "Coupling strength: " << model.getCouplingStrenght() << "\n";

		// Calculating coupling for oscillator 0
        std::cout << "Coupling for oscillator 0: " << model.computeCoupling(0) << "\n";

        std::cout << "KuramotoModel tests completed.\n";
    }

}; // namespace km

#endif TEST_KURAMOTO_HPP
