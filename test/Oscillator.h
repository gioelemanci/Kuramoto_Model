#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <functional>
#include <memory>

namespace km {

	/*
	Represents a generic oscillator in the simulation with a given phase and frequency.
	_theta: phase of the oscillator.
	_omega: natural frequency of the oscillator.
	 */
	class Oscillator {
	protected:
		double _theta;  // Phase
		double _omega;  // Natural Frequency
		// double _x;      // x coordinate
		// double _y;      // y coordinate

		/*
		Manage the phase normalization.
		*/
		void normalizeTheta();

	public:
		Oscillator();
		Oscillator(double theta, double omega);
		virtual ~Oscillator() = default;

		virtual double getOmega() const = 0;
		virtual void setOmega(std::function<double()> ) = 0;

		double getTheta() const;
		void setTheta(double theta);

		/*
		Returns shared pointer to deep copy of the oscillator.
		*/
		virtual std::shared_ptr<Oscillator> clone() const = 0;

		/*
		Print the oscillator state.
		*/
		virtual void printOscillator() const = 0;

	};

	/*
	Represents a standard oscillator.
	Defined with a natural frequency omega.
	 */
	class StdOscillator : public Oscillator {
	public:
		StdOscillator();
		StdOscillator(double theta, double omega);
		StdOscillator(const StdOscillator& copy);

		std::shared_ptr<Oscillator> clone() const override;

		double getOmega() const override;
		void setOmega(std::function<double()>) override;

		void printOscillator() const override;
	};

	/*
	Represents a non linear oscillator, which changes frequency when its phase reaches 0 or \pi.
	It is defined indeed with two natural frequencies, omega and phi.
	 */
	class DoubleOscillator : public Oscillator {
	private:
		double _phi; // Second natural frequency

	public:
		DoubleOscillator();
		DoubleOscillator(double theta, double omega, double phi);
		DoubleOscillator(const DoubleOscillator& copy);

		std::shared_ptr<Oscillator> clone() const override;

		double getOmega() const override;
		void setOmega(std::function<double()> ) override;

		void printOscillator() const override;
	};

}; // namespace km
#endif OSCILLATOR_H