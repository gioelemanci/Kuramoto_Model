#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "Simulation.h"

#include <vector>
#include <utility>
#include <string>

namespace km {
	class KuramotoAnalysis {
	public:
		/*
		Calulate the complex order parameter of the system r(t) at given instant t.
		*/
		static std::pair<double, double> computeOrderParameter(const std::vector<double>& phases);

		/*
		Save the order parameter of the system r(t) in function of t throughtout the simulation to a file.
		*/
		static void saveOrderParameter(const Simulation sim, const std::string& filename);

		/*
		Save the phase distribution at a given instant t to a file.
		*/
		static void savePhaseDistribution(const Simulation sim, const std::string& filename);

		/*
		Save the phases evolution of the oscillators troughout the simulation to a file.
		*/
		static void savePhases(const Simulation sim, const std::string& filename);

		/*
		Save the mean frequencies of the oscillators in the simulation to a file.
		*/
		static void saveMeanFrequencies(const Simulation sim, const std::string& filename);

		/*
		Save phases evolution and order parameter separately for locked and drifting oscillators.
		*/
		void saveLockedDrifting(const Simulation sim, const std::string& filename);

		/*
		Save phases evolution and order parameter separately for each frequency group.
		*/
		void saveByFrequencyGroups(const Simulation& sim, const std::vector<double>& frequencyList, const std::string& filename);
	};
}; // namespace km

#endif ANALYSIS_H
