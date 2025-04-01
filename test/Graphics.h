#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include <cmath>

namespace km {

    class Graphics {
    private:
        sf::RenderWindow _window;
        sf::RenderWindow _circleWindow;
        int _gridSize;  // Grid dimension (number of oscillators per side)
		int _pixelSize; // Dimension of each oscillator in pixels
		static constexpr int windowSize = 1000; // Fixed square window
		static constexpr int circleRadius = 400; // Radius of the circle on which oscillators are placed
        static constexpr int circleCenterX = windowSize / 2;
        static constexpr int circleCenterY = windowSize / 2;
    public:
        Graphics(int numOscillators);

		/*
		Run the simulation in real time.
		*/
        void run(Simulation& sim);

    private:
		/*
		Draw the frame for the grid representation.
        */
        void drawFrame(const Simulation& sim);

		/*
		Draw the frame for the circle representation.
        */
        void drawCircle(const Simulation& sim);

        sf::Color phaseToColor(double phase);
    };

}; // namespace km

#endif // GRAPHICS_H
