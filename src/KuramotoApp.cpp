#include "KuramotoApp.h"
#include "Simulation.h"
#include "SimulationPresets.h"
#include "Graphics.h"
#include "Analysis.h"
#include "Paths.h"
#include <iostream>
#include <vector>

void KuramotoApp::run(int argc, char* argv[]) {
    if (argc > 1) {
        std::string mode = argv[1];
        if (mode == "graphic") runGraphic();
        else if (mode == "step") runStepByStep();
        else if (mode == "multi") runMultiCoupling();
        else {
            std::cerr << "Unknown mode: " << mode << "\n";
            runDefault();
        }
    } else {
        promptUser();
    }
}

void KuramotoApp::promptUser() {
    std::cout << "Select simulation mode:\n";
    std::cout << "1. Graphic simulation\n";
    std::cout << "2. Step-by-step simulation\n";
    std::cout << "3. Multiple coupling simulations\n";
    std::cout << "Choice [1-3]: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1: runGraphic(); break;
        case 2: runStepByStep(); break;
        case 3: runMultiCoupling(); break;
        default: runDefault(); break;
    }
}

void KuramotoApp::saveAnalysis(const km::Simulation& sim, const std::string& suffix) {
    km::paths::ensureDirectoriesExist();
    km::KuramotoAnalysis analysis;

    std::cout << "Saving analysis data...\n";

    analysis.saveOrderParameter(sim, "order_parameter" + suffix + ".txt");
    analysis.savePhaseDistribution(sim, "phase_distribution" + suffix + ".txt");
    analysis.saveMeanFrequencies(sim, "mean_frequencies" + suffix + ".txt");
    analysis.savePhases(sim, "phases" + suffix + ".txt");
    analysis.saveLockedDrifting(sim, suffix);

    std::vector<double> freqGroups = {0.5, 1.0, 1.5, 2.0};
    analysis.saveByFrequencyGroups(sim, freqGroups, suffix);

    std::cout << "Analysis saved successfully.\n";
}

void KuramotoApp::runGraphic() {
    km::Simulation sim = km::sim0(0.1, 250);
    std::cout << "Starting graphic simulation...\n";
    km::Graphics graphics(sim.getModel()->getNumOscillators());
    graphics.run(sim);
    std::cout << "Graphic simulation completed.\n";

    saveAnalysis(sim, "_graphic");
}

void KuramotoApp::runStepByStep() {
    km::Simulation sim = km::sim0(0.1, 250);
    std::cout << "Starting step-by-step simulation...\n";
    for (int step = 0; step < 250; ++step) {
        std::cout << "Step " << step << " completed\n";
        sim.update();
    }
    std::cout << "Step-by-step simulation completed.\n";

    saveAnalysis(sim, "_step");
}

void KuramotoApp::runMultiCoupling() {
    km::Simulation sim = km::sim0(0.1, 250);
    std::vector<double> couplings = {0.1, 0.2, 0.3, 0.4, 0.5};
    std::cout << "Starting multiple coupling simulations...\n";
    for (double c : couplings) {
        std::cout << "Running simulation with coupling strength: " << c << "\n";
        sim.getModel()->setCouplingStrenght(c);
        sim.run();

        std::string suffix = "_multi_" + std::to_string(c);
        saveAnalysis(sim, suffix);

        sim.reset();
    }
    std::cout << "All coupling simulations completed.\n";
}

void KuramotoApp::runDefault() {
    std::cout << "Running default simulation...\n";
    km::Simulation sim = km::sim0(0.1, 250);
    sim.run();
    std::cout << "Default simulation completed.\n";

    saveAnalysis(sim, "_default");
}