#ifndef SIMULATIONPRESETS_H
#define SIMULATIONPRESETS_H

#include "Simulation.h"
#include "Kuramoto.h"
#include "CouplingFunctions.hpp"
#include "FrequencyDistributions.hpp"
#include <iostream>
#include <memory>

namespace km {

	/*
	Standard Kuramoto model:
	- StdOscillators
	- sinusoidal coupling
	- uniform frequency distribution
	*/
	Simulation sim0(double, int);

	/*
	Double Oscillators Kuramoto model:
	- DoubleOscillators
	- sinusoidal coupling
	- uniform frequency distribution
	*/
	Simulation sim1(double, int);

	/*
	List of frequencies Kuramoto model:
	- StdOscillators
	- sinusoidal coupling
	- frequencies from a list
	*/
	Simulation sim2(double, int);

	/*
	Gaussian Kuramoto model:
	- StdOscillators
	- sinusoidal coupling
	- Gaussian frequency distribution
	*/
	Simulation sim3(double, int);

	/*
	Lorenzian Kuramoto model:
	- StdOscillators
	- sinusoidal coupling
	- Lorenzian frequency distribution
	*/
	Simulation sim4(double, int);

	/*
	Double Oscillators Lorenzian Kuramoto model:
	- DoubleOscillators
	- sinusoidal coupling
	- Lorenzian frequency distribution
	*/
	Simulation sim5(double, int);

	/*
	Bimodal Kuramoto model:
	- DoubleOscillators
	- sinusoidal coupling
	- Bimodal frequency distribution
	*/
	Simulation sim6(double, int);

	/*
	Gaussian Kuramoto model:
	- DoubleOscillators
	- sinusoidal coupling
	- Gaussian frequency distribution
	*/
	Simulation sim7(double, int);

}; // namespace km

#endif SIMULATIONPRESETS_H
