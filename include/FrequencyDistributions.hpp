#ifndef FREQUENCYDISTRIBUTIONS_H
#define FREQUENCYDISTRIBUTIONS_H

#include <random>
#include <vector>
#include <functional>

namespace km {

	// Random generator
	static std::random_device rd;
	static std::mt19937 gen(rd());

	// Uniform distribution
	inline double uniformFrequency() {
		static std::uniform_real_distribution<> dist(0, 3);
		return dist(gen);
	}

	// Normal distribution (Gaussian)
	inline std::function<double()> normalFrequency(double mean = 0.0, double stddev = 1.0) {
		return [mean, stddev]() {
			static std::normal_distribution<> dist(mean, stddev);
			return dist(gen);
			};
	}

	// Lorentzian distribution
	inline std::function<double()> lorentzianFrequency(double gamma = 1.0) {
		return [gamma]() {
			static std::cauchy_distribution<> dist(0.0, gamma);
			return dist(gen);
			};
	}

	// Bimodal distribution
	inline std::function<double()> bimodalFrequency() {
		static std::uniform_real_distribution<> distUniform(0.0, 1.0);
		double r = distUniform(gen);
		double p = (r < 0.5) ? 4.5 : 2.5;
		return [p]() {
			static std::normal_distribution<> distNormal(p, 0.2);
			return distNormal(gen);
			};
	}

	// Exponential distribution
	inline std::function<double()> exponentialFrequency(double lambda = 1.0) {
		return [lambda]() {
			static std::exponential_distribution<> dist(lambda);
			return dist(gen);
			};
	}

	class FrequencyDistributor {
	private:
		std::vector<double> frequencies;
		std::shared_ptr<size_t> index;  // Shared among all instances

	public:
		FrequencyDistributor(std::vector<double> freqs)
			: frequencies(std::move(freqs)), index(std::make_shared<size_t>(0)) {
		}

		double operator()() {
			if (frequencies.empty()) return 0.0;
			double frequency = frequencies[*index];
			*index = (*index + 1) % frequencies.size();  // Advance index
			return frequency;
		}
	};


}; // namespace km

#endif // FREQUENCYDISTRIBUTIONS_H
