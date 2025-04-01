#include "Kuramoto.h"
#include "Simulation.h"
#include "SimulationPresets.h"
#include "Graphics.h"
#include "Analysis.h"
#include "CouplingFunctions.hpp"
#include "FrequencyDistributions.hpp"
#include "test_oscillator.hpp"
#include "test_kuramoto.hpp"
#include "test_simulation.hpp"
#include "test_frequency_distributions.hpp"

#include <iostream>
#include <cstdlib>

void stepByStep(km::Simulation sim, int lastStep) {
    for (int step = 0; step < lastStep; ++step) {
        std::cout << "-------------------------\n";
        //for (int i = 0; i < sim.getModel()->getNumOscillators(); ++i) {
        //    std::cout << "  Oscillator " << i << " -> Phase: " << sim.getModel()->getOscillator(i)->getTheta() << "\n";
        //}
        std::cout << "Step " << step << " completato\n";
        sim.update();
    }
}

void test() {
    std::cout << "Running tests...\n";
    std::cout << "-------------------------\n";

    // Test Oscillator classes
    km::testOscillator();
    std::cout << "-------------------------\n";

    // Test Kuramoto Model
    km::testKuramoto();
    std::cout << "-------------------------\n";

    // Test Simulation
    km::testSimulation();
    std::cout << "-------------------------\n";

    // Test Frequency Distributions
    km::testFrequencyDistributions();
    std::cout << "-------------------------\n";

    std::cout << "All tests completed!\n";
}

void graphicSimulation(km::Simulation sim) {
	km::Graphics graphics(sim.getModel()->getNumOscillators());
	graphics.run(sim);  
    std::cout << "Simulazione completata.\n";
}

void saveAnalysis(km::Simulation sim, std::string plus) {
    km::KuramotoAnalysis analysis;

	std::cout << "Saving simulation parameters...\n";

	// Save order parameter
	analysis.saveOrderParameter(sim, "order_parameter" + plus + ".txt");

	// Save phase distribution
	//analysis.savePhaseDistribution(sim, "phase_distribution" + plus + ".txt");

	// Save mean frequencies
	//analysis.saveMeanFrequencies(sim, "mean_frequencies" + plus + ".txt");

	// Save phases
	analysis.savePhases(sim, "phases" + plus + ".txt");

	// Save locked and drifting oscillators
	analysis.saveLockedDrifting(sim, plus);

	// Save by frequency groups
	std::vector<double> freqs = {0.5, 1.0, 1.5, 2.0};
	//analysis.saveByFrequencyGroups(sim, freqs, plus);

	std::cout << "Analysis saved.\n";
}

void multipleCouplingSimulation(km::Simulation sim) {   
	std::vector<double> couplings = {0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

	for (double coupling : couplings) {
		std::cout << "Running simulation with coupling " << coupling << "...\n";
		sim.getModel()->setCouplingStrenght(coupling);
		sim.run();

		std::string plus = "_100_" + std::to_string(coupling);

        km::KuramotoAnalysis analysis;
		analysis.saveOrderParameter(sim, "order_parameter" + plus + ".txt");
		//analysis.savePhases(sim, "phases" + plus + ".txt");
		//analysis.saveMeanFrequencies(sim, "mean_frequencies" + plus + ".txt");

		std::cout << "Simulation " << coupling << " completed.\n\n";
		sim.reset();
	}
}



int main() {
    // Simulation parameters
    double dt = 0.1;
    int maxSteps = 250;
    km::Simulation sim = km::sim4(dt, maxSteps);
    
    std::cout << "Initialization completed! " << sim.getModel()->getNumOscillators() << " oscillators created.\n\n";

	// Run the simulation
	//sim.run();

	multipleCouplingSimulation(sim);

	//stepByStep(sim, maxSteps);

	//graphicSimulation(sim);

	//saveAnalysis(sim, "");

	//test();


    std::cout << "Simulation completed.\n\n";

	sim.printState();

    return 0;
}



