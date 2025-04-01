#include "Simulation.h"
#include <cmath>
#include <iostream>
#include <random>

namespace km {

	Simulation::Simulation() : _dt(0.01), _maxSteps(500), _model() {}
	Simulation::Simulation(double dt, int maxSteps, std::shared_ptr<KuramotoModel> model) : _dt(dt), _maxSteps(maxSteps), _model(model) {}

	double Simulation::getDt() const {
		return _dt;
	}

	int Simulation::getMaxSteps() const {
		return _maxSteps;
	}

    const std::shared_ptr<km::KuramotoModel>& Simulation::getModel() const {
        return _model;
    }

    const std::vector<std::vector<double>>& Simulation::getPhases() const {
		return _phases;
    }

	void Simulation::setDt(double dt) {
		_dt = dt;
	}

	void Simulation::setMaxSteps(int maxSteps) {
		_maxSteps = maxSteps;
	}

	void Simulation::setPhases() {
		_phases.push_back(_model->getPhases());
	}

    void Simulation::setup(KurParams params) {
        for (int i = 0; i < params.numOscillators; ++i) {
            auto osc = params.oscillatorFactory();
            _model->addOscillator(osc);
        }
        _model->setFrequencyDistribution(params.frequencyDistribution);
		_model->setCouplingFunction(params.couplingFunction);
		_model->setCouplingStrenght(params.couplingStrenght);
		_model->setNaturalFrequencies();

        _initialState = std::make_shared<KuramotoModel>(*_model);
    }

	void Simulation::reset() {
		_phases.clear();
		*_model = *_initialState;
	}

    void Simulation::update() {
        int N = _model->getNumOscillators();
        std::vector<double> k1(N), k2(N), k3(N), k4(N);

        // k1
        for (int i = 0; i < N; ++i) {
            k1[i] = _dt * (_model->getOscillator(i)->getOmega() + _model->computeCoupling(i));
        }

        // k2
        for (int i = 0; i < N; ++i) {
            _model->getOscillator(i)->setTheta(_model->getOscillator(i)->getTheta() + k1[i] / 2);
        }
        for (int i = 0; i < N; ++i) {
            k2[i] = _dt * (_model->getOscillator(i)->getOmega() + _model->computeCoupling(i));
        }

        // k3
        for (int i = 0; i < N; ++i) {
            _model->getOscillator(i)->setTheta(_model->getOscillator(i)->getTheta() - k1[i] / 2 + k2[i] / 2);
        }
        for (int i = 0; i < N; ++i) {
            k3[i] = _dt * (_model->getOscillator(i)->getOmega() + _model->computeCoupling(i));
        }

        // k4
        for (int i = 0; i < N; ++i) {
            _model->getOscillator(i)->setTheta(_model->getOscillator(i)->getTheta() - k2[i] / 2 + k3[i]);
        }
        for (int i = 0; i < N; ++i) {
            k4[i] = _dt * (_model->getOscillator(i)->getOmega() + _model->computeCoupling(i));
        }

        // Final phase update
        for (int i = 0; i < N; ++i) {
            double newTheta = _model->getOscillator(i)->getTheta() + (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6;

            _model->getOscillator(i)->setTheta(newTheta);
        }
		Simulation::setPhases();
    }

    void Simulation::run() {
        for (int t = 0; t < _maxSteps; ++t) {
            update();
            std::cout << "Step " << t << " completed" << std::endl;
        }
    }

	void Simulation::printState() const {

		std::cout << "Simulation state:" << std::endl;
		std::cout << "---------------------------" << std::endl;
		std::cout << "Number of oscillators: " << _model->getNumOscillators() << std::endl;
		std::cout << "Coupling strength: " << _model->getCouplingStrenght() << std::endl;
		std::cout << "Oscillators state: " << std::endl;
        for (int i = 0; i < _model->getNumOscillators(); ++i) {
            std::cout << "  Oscillator " << i + 1 << ": ";
            _model->getOscillator(i)->printOscillator();
        }
	}
}; // namespace km
