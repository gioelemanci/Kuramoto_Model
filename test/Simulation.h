#ifndef SIMULATION_H
#define SIMULATION_H

#include "Kuramoto.h"

namespace km {

	/*
	Input parameters for the Kuramoto model.
	- oscillatorFactory: function that creates an oscillator of the desired class.
	- couplingFunction: function that defines the coupling between oscillators.
	- frequencyDistribution: function that defines the distribution of natural frequencies.
	- couplingStrenght: global coupling strength.
	- numOscillators: number of oscillators in the model.
	 */
	struct KurParams {
		std::function<std::shared_ptr<Oscillator>()> oscillatorFactory;
		std::function<double(double, double)> couplingFunction;
		std::function<double()> frequencyDistribution;
		double couplingStrenght;
		int numOscillators;
	};

	/*
	Class responsible for temporal evolution of the model and practical interface.
	_dt: time step.
	_maxSteps: maximum number of steps.
	_model: shared pointer to the Kuramoto model.
	_phases: vector of vectors containing the phases of the oscillators at each step.
	_params: struct containing parameters to initialize the Kuramoto model.
	 */
	class Simulation {
	private:
		double _dt;
		int _maxSteps;
		std::shared_ptr<KuramotoModel> _model;
		std::vector<std::vector<double>> _phases;

		std::shared_ptr<KuramotoModel> _initialState;

	public:
		Simulation();
		Simulation(double dt, int maxSteps, std::shared_ptr<KuramotoModel> model);
		~Simulation() = default;

		double getDt() const;
		int getMaxSteps() const;
		const std::shared_ptr<km::KuramotoModel>& getModel() const;
		const std::vector<std::vector<double>>& getPhases() const;


		void setDt(double);
		void setMaxSteps(int);
		void setPhases();

		/*
		Initialize the Kuramoto model with the given parameters, creating the oscillators and setting coupling and frequencies.
		 */
		void setup(KurParams);

		/*
		Reset the simulation, clearing the phases vector and istantiating a new model. To call always after setup.
		 */
		void reset();

		/*
		Updates the model state with Runge-Kutta 4th order method.
		 */
		void update();

		/*
		Run the simulation for a number of steps.
		 */
		void run();

		/*
		Print the state of the model in the simulation at given step.
		*/
		void printState() const;
	};

}; // namespace km

#endif SIMULATION_H
