#include "Oscillator.h"
#include <cmath>
#include <random>
#include <iostream>

auto const M_PI = 3.14159265358979323846;

namespace km {

	 double randomPhase() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dist(0.0, 2.0 * M_PI);
		return dist(gen);
	}

// Oscillator class implementation

	void Oscillator::normalizeTheta() {
		_theta = fmod(_theta, 2.0 * M_PI); // floating point version of the modulo operator (theta comprised between -2\pi and 2\pi)
		if (_theta < 0)
			_theta += 2.0 * M_PI;
	}

	Oscillator::Oscillator() : _theta(randomPhase()), _omega(0.0) {}
	Oscillator::Oscillator(double theta, double omega) : _theta(theta), _omega(omega) { normalizeTheta(); }

	double Oscillator::getTheta() const { return _theta; }

	void Oscillator::setTheta(double theta) {
		this->_theta = theta;
		normalizeTheta();
	}


// StdOscillator class implementation

	StdOscillator::StdOscillator() : Oscillator() {}
	StdOscillator::StdOscillator(double theta, double omega) : Oscillator(theta, omega) {}
	StdOscillator::StdOscillator(const StdOscillator& copy) : Oscillator(copy._theta, copy._omega) {}

	std::shared_ptr<Oscillator> StdOscillator::clone() const {
		return std::make_shared<StdOscillator>(*this);
	}

	double StdOscillator::getOmega() const {
		return this->_omega;
	}

	void StdOscillator::setOmega(std::function<double()> distribution) { this->_omega = distribution(); }

	void StdOscillator::printOscillator() const {
		std::cout << "Phase: " << _theta << " Frequency: " << _omega << std::endl;
		//std::cout << "Position: " << _x << ", " << _y << std::endl;
	}


// DoubleOscillator class implementation

	DoubleOscillator::DoubleOscillator() : Oscillator(), _phi(0.0) {}
	DoubleOscillator::DoubleOscillator(double theta, double omega, double phi) : Oscillator(theta, omega), _phi(phi) {}
	DoubleOscillator::DoubleOscillator(const DoubleOscillator& copy) : Oscillator(copy._theta, copy._omega), _phi(copy._phi) {}

	std::shared_ptr<Oscillator> DoubleOscillator::clone() const {
		return std::make_shared<DoubleOscillator>(*this);
	}

	double DoubleOscillator::getOmega() const {
		if (this->_theta < M_PI) {
			return _omega;
		}
		else { return _phi; }
	}

	void DoubleOscillator::setOmega(std::function<double()> distribution) {
		this->_omega = distribution(); 
		this->_phi = distribution();

		if ((_omega > 0 && _phi < 0) || (_omega < 0 && _phi > 0)) {
			_phi = -_phi;
		}  // Having two natural frequencies with opposed signs can lead to errors
	}

	void DoubleOscillator::printOscillator() const {
		std::cout << "Phase: " << _theta << " Frequency I: " << _omega << " Frequency II: " << _phi << std::endl;
		//std::cout << "Position: " << _x << ", " << _y << std::endl;
	}


}; // namespace km