#ifndef KURAMOTO_H
#define KURAMOTO_H

#include "Oscillator.h"
#include <vector>
#include <functional>
#include <memory>

namespace km {
	/*
	 Class responsible for all direct actions on the oscillators.
	 _oscillators: vector of shared_ptr to the oscillators.
	 _couplingFunction: function that computes the coupling between two oscillators.
	 _frequencyDistribution: function that assigns the natural frequency to the oscillators.
	 _couplingStrenght: global coupling strenght.
	 */
	class KuramotoModel {
	private:
		std::vector<std::shared_ptr<km::Oscillator>> _oscillators;
		std::function<double(double, double)> _couplingFunction;
		std::function<double()> _frequencyDistribution;

		double _couplingStrenght;


	public:
		KuramotoModel();
		KuramotoModel(const KuramotoModel& copy);
		~KuramotoModel() = default;

		KuramotoModel& operator=(const KuramotoModel& copy);

		void addOscillator(std::shared_ptr<km::Oscillator>);
		void setCouplingFunction(std::function<double(double, double)>);
		void setFrequencyDistribution(std::function<double()>);
		void setCouplingStrenght(double);

		/*
		Initialize the natural frequencies of the oscillators.
		*/
		void setNaturalFrequencies();

		double getCouplingStrenght() const;
		int getNumOscillators() const;

		/*
		Returns shared_ptr to the oscillator at index i.
		*/
		std::shared_ptr<Oscillator> getOscillator(int i) const;

		/*
		Returns a vector of shared_ptr to all oscillators.
		*/
		std::vector<std::shared_ptr<Oscillator>> getOscillators() const;

		/*
		Returns a vector of the phases of all oscillators.
		*/
		const std::vector<double> getPhases() const;

		/*
		Returns the coupling for oscillator i, considering interactions among every oscillator.
		*/
		double computeCoupling(int);

		/*
		Returns a vector with natural frequencies of all oscillators.
		*/
		std::vector<double> getNaturalFrequencies() const;
	};

}; // namespace km
#endif KURAMOTO_H
