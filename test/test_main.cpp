#include "test_oscillator.hpp"
#include "test_kuramoto.hpp"
#include "test_simulation.hpp"
#include "test_frequency_distributions.hpp"
#include <iostream>

int main() {
    std::cout << "Running tests...\n";

    km::testOscillator();
    km::testKuramoto();
    km::testSimulation();
    km::testFrequencyDistributions();

    std::cout << "All tests completed!\n";
    return 0;
}
