#include "Kuramoto.h"

namespace km {
	KuramotoModel::KuramotoModel() : 
		_oscillators(), 
		_couplingFunction([](double theta_i, double theta_j) { return sin(theta_j - theta_i); }),
		_frequencyDistribution([]() { return 0.0; }),
		_couplingStrenght(0.0) {}
	KuramotoModel::KuramotoModel(const KuramotoModel& copy) {
		*this = copy;
	}

	KuramotoModel& KuramotoModel::operator=(const KuramotoModel& copy) {
		if (this != &copy) {
			_oscillators.clear();
			for (const auto& osc : copy._oscillators) {
				_oscillators.push_back(osc->clone());
			}
			_couplingFunction = copy._couplingFunction;
			_frequencyDistribution = copy._frequencyDistribution;
			_couplingStrenght = copy._couplingStrenght;
		}
		return *this;
	}

	void KuramotoModel::addOscillator(std::shared_ptr<km::Oscillator> oscillator) {
		_oscillators.push_back(oscillator);
	}

	void KuramotoModel::setCouplingFunction(std::function<double(double, double)> couplingFunction) {
		this->_couplingFunction = couplingFunction;
	}

	void KuramotoModel::setFrequencyDistribution(std::function<double()> frequencyDistribution) {
		this->_frequencyDistribution = frequencyDistribution;
	}

	void KuramotoModel::setNaturalFrequencies() {
		for (auto& osc : _oscillators) {
			osc->setOmega(_frequencyDistribution);
		}		
	}

	void KuramotoModel::setCouplingStrenght(double couplingStrenght) {
		this->_couplingStrenght = couplingStrenght;
	}

	double KuramotoModel::getCouplingStrenght() const {
		return _couplingStrenght;
	}

	int KuramotoModel::getNumOscillators() const {
		return _oscillators.size();
	}

	std::shared_ptr<Oscillator> KuramotoModel::getOscillator(int i) const {
		return _oscillators[i];
	}

	std::vector<std::shared_ptr<Oscillator>> KuramotoModel::getOscillators() const {
		return _oscillators;
	}

	const std::vector<double> KuramotoModel::getPhases() const {
		std::vector<double> phases;
		for (auto& osc : _oscillators) {
			phases.push_back(osc->getTheta());
		}
		return phases;
	}

	double KuramotoModel::computeCoupling(int i) {
		double k = _couplingStrenght / _oscillators.size();
		double sum = 0.0;
		for (int j = 0; j < _oscillators.size(); ++j) {
			if (i != j) {
				sum += _couplingFunction(_oscillators[i]->getTheta(), _oscillators[j]->getTheta());
			}
		}
		return k * sum;
	}

	std::vector<double> KuramotoModel::getNaturalFrequencies() const {
		std::vector<double> freqs;
		freqs.reserve(_oscillators.size());

		for (const auto& oscillator : _oscillators) {
			freqs.push_back(oscillator->getOmega());
		}
		return freqs;
	}



}; // namespace km
