#ifndef TEST_SIMULATION_HPP
#define TEST_SIMULATION_HPP

#include <iostream>
#include "Simulation.h"
#include "Oscillator.h"

namespace km {
    void testSimulation() {
        std::cout << "Testing Simulation class...\n";

        std::shared_ptr<KuramotoModel> model = std::make_shared<KuramotoModel>();
        Simulation sim(0.01, 10, model);

        KurParams params;
        params.oscillatorFactory = []() { return std::make_shared<StdOscillator>(); };
        params.couplingFunction = [](double theta_i, double theta_j) { return sin(theta_j - theta_i); };
        params.frequencyDistribution = []() { return 1.0; };
        params.couplingStrenght = 0.5;
        params.numOscillators = 5;

        std::cout << "Setting up simulation with " << params.numOscillators << " oscillators...\n";
        sim.setup(params);

        std::cout << "Initial phases:\n";
        for (const auto& phase : sim.getModel()->getPhases()) {
            std::cout << phase << " ";
        }
        std::cout << "\n";

        sim.run();

        std::cout << "Final phases:\n";
        for (const auto& phase : sim.getModel()->getPhases()) {
            std::cout << phase << " ";
        }
        std::cout << "\n";

        std::cout << "Simulation tests completed.\n";
    }

}; // namespace km

#endif // TEST_SIMULATION_HPP
