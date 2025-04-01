#include "Analysis.h"

#include <cmath>
#include <complex>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <map>


namespace fs = std::filesystem;
auto const M_PI = 3.14159265358979323846;
static const std::string projectDir = "C:/Users/manci/source/repos/Kuramoto_Model/test/";


namespace km {

    std::pair<double, double> KuramotoAnalysis::computeOrderParameter(const std::vector<double>& phases) {
        int numOscillators = phases.size();
        std::complex<double> sum(0.0, 0.0);

        if (numOscillators == 0) {
            return std::make_pair(0.0, 0.0);
        }

        for (double theta : phases) {
            sum += exp(std::complex<double>(0, theta));  // e^(i\theta)
        }

		double r = abs(sum) / numOscillators;   // Order parameter amplitude
		double psi = atan2(sum.imag(), sum.real()); // Mean phase

		// Normalize the phase
        if (psi < 0) {
            psi += 2 * M_PI;
        }

        return std::make_pair(r, psi);
    }

    void KuramotoAnalysis::saveOrderParameter(const Simulation sim, const std::string& filename) {
        auto phases = sim.getPhases();
		std::string filepath = projectDir + filename;

        std::ofstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error while opening the file " << filepath << std::endl;
            return;
        }

        file << "time r psi\n";
        for (size_t t = 0; t < phases.size(); ++t) {
            std::pair<double, double> orderParam = computeOrderParameter(phases[t]);
            file << t * sim.getDt() << " " << orderParam.first << " " << orderParam.second << "\n";
        }

        file.close();
    }

    void KuramotoAnalysis::savePhaseDistribution(const Simulation sim, const std::string& filename) {
        auto phases = sim.getPhases()[0];
        std::string filepath = projectDir + filename;

        std::ofstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error while opening the file " << filepath << std::endl;
            return;
        }

        file << "phase\n";
        for (double phase : phases) {
            file << phase << "\n";
        }
        file.close();
    }

    void KuramotoAnalysis::saveMeanFrequencies(const Simulation sim, const std::string& filename) {
        double dt = sim.getDt();
        auto phases = sim.getPhases();
        int numOscillators = phases[0].size();
        int numTimesteps = phases.size();

        std::string filepath = projectDir + filename;

        std::ofstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error while opening the file " << filepath << std::endl;
            return;
        }

        file << "mean_frequency\n";
        for (int i = 0; i < numOscillators; ++i) {
            auto ph = (phases[numTimesteps - 1][i] - phases[0][i]) / (dt * numTimesteps);
            file << ph << "\n";
        }
        file.close();
    }

    void KuramotoAnalysis::savePhases(const Simulation sim, const std::string& filename) {
        auto phases = sim.getPhases();
        int numTimesteps = phases.size();
        int numOscillators = phases[0].size();
        std::string filepath = projectDir + filename;

        std::ofstream file(filepath);

        if (!file.is_open()) {
            std::cerr << "Error while opening the file " << filepath << std::endl;
            return;
        }

        file << "time";
        for (int i = 0; i < numOscillators; ++i) {
            file << " osc" << i + 1;
        }
        file << std::endl;

		for (int t = 0; t < numTimesteps; ++t) {
			file << t * sim.getDt();  // time (t * dt)
			for (int i = 0; i < numOscillators; ++i) {
				file << " " << phases[t][i];
			}
			file << std::endl;
		}
		file.close();

    }
    
    void KuramotoAnalysis::saveLockedDrifting(const Simulation sim, const std::string& filename) {
        auto phases = sim.getPhases();
        int numTimesteps = phases.size();
        int numOscillators = phases[0].size();
        double dt = sim.getDt();
        double K = sim.getModel()->getCouplingStrenght();

        std::vector<double> meanFrequencies(numOscillators, 0.0);

        // Compute order parameter and mean frequency
        for (int i = 0; i < numOscillators; ++i) {
            meanFrequencies[i] = (phases[numTimesteps - 1][i] - phases[0][i]) / (dt * numTimesteps);
        }

        auto orderParam = KuramotoAnalysis::computeOrderParameter(phases[numTimesteps - 1]);
        double r = orderParam.first;
        double avgOmega = 0.0;

        for (double omega : meanFrequencies) {
            avgOmega += omega;
        }
        avgOmega /= numOscillators;

        double threshold = K * r;

        // Distinguish between locked and drifting
        std::vector<int> lockedOscillators, driftingOscillators;
        for (int i = 0; i < numOscillators; ++i) {
            if (std::abs(meanFrequencies[i] - avgOmega) < threshold) {
                lockedOscillators.push_back(i);
            }
            else {
                driftingOscillators.push_back(i);
            }
        }

        // Output file for locked
        std::ofstream lockedPhasesFile(projectDir + filename + "_locked_phases.txt");
        std::ofstream lockedOrderParamFile(projectDir + filename + "_locked_order_parameter.txt");

        if (!lockedPhasesFile.is_open() || !lockedOrderParamFile.is_open()) {
            std::cerr << "Error opening file for locked oscillators." << std::endl;
            return;
        }

        lockedPhasesFile << "time";
        for (int i : lockedOscillators) {
            lockedPhasesFile << " osc" << i + 1;
        }
        lockedPhasesFile << "\n";

        lockedOrderParamFile << "time r_locked psi_locked\n";

        for (int t = 0; t < numTimesteps; ++t) {
            std::vector<double> lockedPhases;
            for (int i : lockedOscillators) {
                lockedPhases.push_back(phases[t][i]);
            }
            auto orderParamLocked = KuramotoAnalysis::computeOrderParameter(lockedPhases);
            double r_locked = orderParamLocked.first;
            double psi_locked = orderParamLocked.second;

            lockedPhasesFile << t * dt;
            for (double phase : lockedPhases) {
                lockedPhasesFile << " " << phase;
            }
            lockedPhasesFile << "\n";

            lockedOrderParamFile << t * dt << " " << r_locked << " " << psi_locked << "\n";
        }

        lockedPhasesFile.close();
        lockedOrderParamFile.close();

        // Output file for drifting
        std::ofstream driftingPhasesFile(projectDir + filename + "_drifting_phases.txt");
        std::ofstream driftingOrderParamFile(projectDir + filename + "_drifting_order_parameter.txt");

        if (!driftingPhasesFile.is_open() || !driftingOrderParamFile.is_open()) {
            std::cerr << "Error opening file for drifting oscillators." << std::endl;
            return;
        }

        driftingPhasesFile << "time";
        for (int i : driftingOscillators) {
            driftingPhasesFile << " osc" << i + 1;
        }
        driftingPhasesFile << "\n";

        driftingOrderParamFile << "time r_drifting psi_drifting\n";

        for (int t = 0; t < numTimesteps; ++t) {
            std::vector<double> driftingPhases;
            for (int i : driftingOscillators) {
                driftingPhases.push_back(phases[t][i]);
            }
            auto orderParamDrifting = KuramotoAnalysis::computeOrderParameter(driftingPhases);
            double r_drifting = orderParamDrifting.first;
            double psi_drifting = orderParamDrifting.second;

            driftingPhasesFile << t * dt;
            for (double phase : driftingPhases) {
                driftingPhasesFile << " " << phase;
            }
            driftingPhasesFile << "\n";

            driftingOrderParamFile << t * dt << " " << r_drifting << " " << psi_drifting << "\n";
        }

        driftingPhasesFile.close();
        driftingOrderParamFile.close();

        std::cout << "Locked oscillators: " << lockedOscillators.size() << " saved in " << filename + "_locked_phases.txt" << std::endl;
        std::cout << "Drifting oscillators: " << driftingOscillators.size() << " saved in " << filename + "_drifting_phases.txt" << std::endl;
    }

    void KuramotoAnalysis::saveByFrequencyGroups(const Simulation& sim, const std::vector<double>& natFreqs, const std::string& filename) {
        auto phases = sim.getPhases();
        int numTimesteps = phases.size();

        if (phases.empty()) {
            std::cerr << "Error: No phase data available!" << std::endl;
            return;
        }

        int numOscillators = sim.getModel()->getNumOscillators();
        std::vector<double> allFrequencies = sim.getModel()->getNaturalFrequencies();

        if (allFrequencies.size() != numOscillators) {
            std::cerr << "Error: Mismatch between number of frequencies (" << allFrequencies.size()
                << ") and oscillators (" << numOscillators << ")!" << std::endl;
            return;
        }

        double dt = sim.getDt();

        // Map each unique frequency to the corresponding oscillators
        std::map<double, std::vector<int>> frequencyGroups;
        for (int i = 0; i < numOscillators; ++i) {
            frequencyGroups[allFrequencies[i]].push_back(i);
        }

        for (double freq : natFreqs) {
            if (frequencyGroups.find(freq) == frequencyGroups.end()) {
                std::cerr << "Warning: No oscillators found for frequency " << freq << std::endl;
                continue;
            }

            const std::vector<int>& indices = frequencyGroups[freq];

            std::string freqStr = std::to_string(freq);
            std::replace(freqStr.begin(), freqStr.end(), '.', '_'); // Ensure valid filename format

            std::ofstream phaseFile(projectDir + filename + "_freq_" + freqStr + "_phases.txt");
            std::ofstream orderParamFile(projectDir + filename + "_freq_" + freqStr + "_order_parameter.txt");

            if (!phaseFile.is_open() || !orderParamFile.is_open()) {
                std::cerr << "Error opening files for frequency " << freq << std::endl;
                continue;
            }

            phaseFile << "time";
            for (int i : indices) {
                phaseFile << " osc" << i + 1;
            }
            phaseFile << "\n";

            orderParamFile << "time r psi\n";

            for (int t = 0; t < numTimesteps; ++t) {
                std::vector<double> groupPhases;
                for (int i : indices) {
                    if (i >= phases[t].size()) {
                        std::cerr << "Error: Oscillator index " << i << " out of range at timestep " << t << std::endl;
                        return;
                    }
                    groupPhases.push_back(phases[t][i]);
                }

                auto orderParam = KuramotoAnalysis::computeOrderParameter(groupPhases);
                double r = orderParam.first;
                double psi = orderParam.second;

                phaseFile << t * dt;
                for (double phase : groupPhases) {
                    phaseFile << " " << phase;
                }
                phaseFile << "\n";

                orderParamFile << t * dt << " " << r << " " << psi << "\n";
            }

            phaseFile.close();
            orderParamFile.close();

            std::cout << "Saved phases and order parameter for freq " << freq << " in files: "
                << filename + "_freq_" + freqStr + "_phases.txt" << " and "
                << filename + "_freq_" + freqStr + "_order_parameter.txt" << std::endl;
        }
    }




}; // namespace km

