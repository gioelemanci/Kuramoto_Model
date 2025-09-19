#include "KuramotoApp.h"
#include "Simulation.h"
#include "SimulationPresets.h"
#include "Graphics.h"
#include "Analysis.h"
#include "Paths.h"
#include <iostream>
#include <vector>

void KuramotoApp::run(int argc, char* argv[]) {
    if (argc > 2) {
        presetIndex = std::stoi(argv[2]);
    } else {
        selectPreset();
    }

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


void KuramotoApp::selectPreset() {
    std::cout << "Select simulation preset:\n";
    std::cout << "0. Standard oscillator, uniform frequency\n";
    std::cout << "1. Double oscillator, uniform frequency\n";
    std::cout << "2. Standard oscillator, custom frequency list\n";
    std::cout << "3. Standard oscillator, Gaussian frequency\n";
    std::cout << "4. Standard oscillator, Lorentzian frequency\n";
    std::cout << "5. Double oscillator, Lorentzian frequency\n";
    std::cout << "6. Standard oscillator, bimodal frequency\n";
    std::cout << "7. Double oscillator, Gaussian frequency\n";
    std::cout << "Choice [0-7]: ";

    std::cin >> presetIndex;
    if (presetIndex < 0 || presetIndex > 7) {
        std::cerr << "Invalid preset. Defaulting to sim0.\n";
        presetIndex = 0;
    }
}

km::Simulation KuramotoApp::createSimulation() const {
    double dt = 0.1;
    int maxSteps = 250;

    switch (presetIndex) {
        case 1: return km::sim1(dt, maxSteps);
        case 2: return km::sim2(dt, maxSteps);
        case 3: return km::sim3(dt, maxSteps);
        case 4: return km::sim4(dt, maxSteps);
        case 5: return km::sim5(dt, maxSteps);
        case 6: return km::sim6(dt, maxSteps);
        case 7: return km::sim7(dt, maxSteps);
        default: return km::sim0(dt, maxSteps);
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
    km::Simulation sim = createSimulation();
    std::cout << "Starting graphic simulation...\n";
    km::Graphics graphics(sim.getModel()->getNumOscillators());
    graphics.run(sim);
    std::cout << "Graphic simulation completed.\n";
}

void KuramotoApp::runStepByStep() {
    km::Simulation sim = createSimulation();
    std::cout << "Starting step-by-step simulation...\n";
    for (int step = 0; step < 250; ++step) {
        std::cout << "Step " << step << " completed\n";
        sim.update();
    }
    std::cout << "Step-by-step simulation completed.\n";
}

void KuramotoApp::runMultiCoupling() {
    km::Simulation sim = createSimulation();
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
    km::Simulation sim = createSimulation();
    sim.run();
    std::cout << "Default simulation completed.\n";

    saveAnalysis(sim, "_default");
}