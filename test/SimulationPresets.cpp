#include "SimulationPresets.h"

namespace km{

	Simulation sim0(double dt, int maxSteps) {
		// Instantiate the Kuramoto model
		std::shared_ptr<km::KuramotoModel> model = std::make_shared<km::KuramotoModel>();

		// Setting model parameters
		km::KurParams params = { 
			[]() {return std::make_shared<km::StdOscillator>();}, // Standard oscillator
			km::sinusoidalCoupling, // Sinusoidal coupling function (kuramoto standard)
			km::uniformFrequency, // Uniform frequency distribution
			1.8, // Global coupling strength
			1000 }; // Number of oscillators

		// Create the simulation
		Simulation sim = Simulation(dt, maxSteps, model);
		sim.setup(params);

		return sim;
	}



	Simulation sim1(double dt, int maxSteps) {
		// Instantiate the Kuramoto model
		std::shared_ptr<km::KuramotoModel> model = std::make_shared<km::KuramotoModel>();

		// Setting model parameters
		km::KurParams params = {
			[]() {return std::make_shared<km::DoubleOscillator>();}, // Double oscillator
			km::sinusoidalCoupling, // Sinusoidal coupling function (kuramoto standard)
			km::uniformFrequency, // Uniform frequency distribution
			1.0, // Global coupling strength
			100 }; // Number of oscillators

		// Create the simulation
		Simulation sim = Simulation(dt, maxSteps, model);
		sim.setup(params);

		return sim;
	}


	Simulation sim2(double dt, int maxSteps) {
		// Instantiate the Kuramoto model
		std::shared_ptr<km::KuramotoModel> model = std::make_shared<km::KuramotoModel>();

		// Setting model parameters
		std::vector<double> list = { 0.5 };//, 1.0, 1.5, 2.0 };
		km::KurParams params = {
			[]() {return std::make_shared<km::StdOscillator>();}, // Standard oscillator
			km::sinusoidalCoupling, // Sinusoidal coupling function (kuramoto standard)
			km::FrequencyDistributor(list), // Frequency distributor from list
			1.0, // Global coupling strength
			1000 }; // Number of oscillators

		// Create the simulation
		Simulation sim = Simulation(dt, maxSteps, model);
		sim.setup(params);
		return sim;
	}


	Simulation sim3(double dt, int maxSteps) {
		// Instantiate the Kuramoto model
		std::shared_ptr<km::KuramotoModel> model = std::make_shared<km::KuramotoModel>();
		// Setting model parameters
		km::KurParams params = {
			[]() {return std::make_shared<km::StdOscillator>();}, // Standard oscillator
			km::sinusoidalCoupling, // Sinusoidal coupling function (kuramoto standard)
			km::normalFrequency(0, .2), // Gaussian frequency distribution
			1, // Global coupling strength
			1000 }; // Number of oscillators
		// Create the simulation
		Simulation sim = Simulation(dt, maxSteps, model);
		sim.setup(params);
		return sim;
	}



	Simulation sim4(double dt, int maxSteps) {
		// Instantiate the Kuramoto model
		std::shared_ptr<km::KuramotoModel> model = std::make_shared<km::KuramotoModel>();

		// Setting model parameters
		km::KurParams params = {
			[]() {return std::make_shared<km::StdOscillator>();}, // Standard oscillator
			km::sinusoidalCoupling, // Sinusoidal coupling function (kuramoto standard)
			km::lorentzianFrequency(0.2), // Lorentzian frequency distribution
			1., // Global coupling strength
			100 }; // Number of oscillators

		// Create the simulation
		Simulation sim = Simulation(dt, maxSteps, model);
		sim.setup(params);

		return sim;
	}


	Simulation sim5(double dt, int maxSteps) {
		// Instantiate the Kuramoto model
		std::shared_ptr<km::KuramotoModel> model = std::make_shared<km::KuramotoModel>();
		// Setting model parameters
		km::KurParams params = {
			[]() {return std::make_shared<km::DoubleOscillator>();}, // Double oscillator
			km::sinusoidalCoupling, // Sinusoidal coupling function (kuramoto standard)
			km::lorentzianFrequency(0.4), // Lorentzian frequency distribution
			1.0, // Global coupling strength
			1000 }; // Number of oscillators
		// Create the simulation
		Simulation sim = Simulation(dt, maxSteps, model);
		sim.setup(params);
		return sim;
	}

	Simulation sim6(double dt, int maxSteps) {
		// Instantiate the Kuramoto model
		std::shared_ptr<km::KuramotoModel> model = std::make_shared<km::KuramotoModel>();
		// Setting model parameters
		km::KurParams params = {
			[]() {return std::make_shared<km::StdOscillator>();}, // Standard oscillator
			km::sinusoidalCoupling, // Sinusoidal coupling function (kuramoto standard)
			km::bimodalFrequency(), // Bimodal frequency distribution
			1.0, // Global coupling strength
			100 }; // Number of oscillators
		// Create the simulation
		Simulation sim = Simulation(dt, maxSteps, model);
		sim.setup(params);
		return sim;
	}

	Simulation sim7(double dt, int maxSteps) {
		// Instantiate the Kuramoto model
		std::shared_ptr<km::KuramotoModel> model = std::make_shared<km::KuramotoModel>();
		// Setting model parameters
		km::KurParams params = {
			[]() {return std::make_shared<km::DoubleOscillator>();}, // Double oscillator
			km::sinusoidalCoupling, // Sinusoidal coupling function (kuramoto standard)
			km::normalFrequency(0, 0.5), // Gaussian frequency distribution
			1.0, // Global coupling strength
			1000 }; // Number of oscillators
		// Create the simulation
		Simulation sim = Simulation(dt, maxSteps, model);
		sim.setup(params);
		return sim;
	}

}; // namespace km