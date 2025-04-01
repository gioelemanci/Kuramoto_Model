#include "graphics.h"
#include "analysis.h"

auto const M_PI = 3.14159265358979323846;

namespace km {
    Graphics::Graphics(int numOscillators) {
		_gridSize = static_cast<int>(std::ceil(std::sqrt(numOscillators))); // Square grid
		_pixelSize = windowSize / _gridSize;  // Adjust the size of the pixels

        _window.create(sf::VideoMode(windowSize, windowSize), "Kuramoto Simulation (Grid)");
        _window.setFramerateLimit(60);

        _circleWindow.create(sf::VideoMode(windowSize, windowSize), "Kuramoto Simulation (Circle)");
        _circleWindow.setFramerateLimit(60);
    }

    sf::Color Graphics::phaseToColor(double phase) {
        int r = static_cast<int>(127.5 * (1 + std::cos(phase)));
        int g = static_cast<int>(127.5 * (1 + std::cos(phase + 2 * M_PI / 3)));
        int b = static_cast<int>(127.5 * (1 + std::cos(phase + 4 * M_PI / 3)));
        return sf::Color(r, g, b);
    }

    void Graphics::drawFrame(const Simulation& sim) {
        _window.clear();

        auto oscillators = sim.getModel()->getOscillators();

        for (int i = 0; i < oscillators.size(); ++i) {
            int x = (i % _gridSize) * _pixelSize;
            int y = (i / _gridSize) * _pixelSize;

            sf::RectangleShape pixel(sf::Vector2f(_pixelSize, _pixelSize));
            pixel.setPosition(x, y);
            pixel.setFillColor(phaseToColor(oscillators[i]->getTheta()));
            _window.draw(pixel);
        }

        _window.display();
    }

    void Graphics::drawCircle(const Simulation& sim) {
        _circleWindow.clear(sf::Color::White); // White background

        auto model = sim.getModel();
        auto oscillators = model->getOscillators();

        // Draw axis
        sf::Vertex xAxis[] = {
            sf::Vertex(sf::Vector2f(0, circleCenterY), sf::Color::Black),
            sf::Vertex(sf::Vector2f(windowSize, circleCenterY), sf::Color::Black)
        };
        sf::Vertex yAxis[] = {
            sf::Vertex(sf::Vector2f(circleCenterX, 0), sf::Color::Black),
            sf::Vertex(sf::Vector2f(circleCenterX, windowSize), sf::Color::Black)
        };

        _circleWindow.draw(xAxis, 2, sf::Lines);
        _circleWindow.draw(yAxis, 2, sf::Lines);

        // Draw oscillators on the circumference
        for (int i = 0; i < oscillators.size(); ++i) {
            double phase = oscillators[i]->getTheta();
            double angle = phase;

            int x = static_cast<int>(circleCenterX + circleRadius * std::cos(angle));
            int y = static_cast<int>(circleCenterY + circleRadius * std::sin(angle));

            sf::CircleShape ball(6);  // Radius in pixels
            ball.setPosition(x - 6, y - 6);  // Center circle in the position
            ball.setFillColor(phaseToColor(phase));

            _circleWindow.draw(ball);
        }

        // Compute order parameter
        std::vector<double> phases = sim.getModel()->getPhases();

        std::pair<double, double> orderParam = KuramotoAnalysis::computeOrderParameter(phases);

        // Draw r of order parameter
        double endX = circleCenterX + (orderParam.first * circleRadius) * std::cos(orderParam.second);
        double endY = circleCenterY + (orderParam.first * circleRadius) * std::sin(orderParam.second);

        sf::Vertex orderLine[] = {
            sf::Vertex(sf::Vector2f(circleCenterX, circleCenterY), sf::Color::Black),
            sf::Vertex(sf::Vector2f(endX, endY), sf::Color::Black)
        };
        _circleWindow.draw(orderLine, 2, sf::Lines);

        _circleWindow.display();
    }


    void Graphics::run(Simulation& sim) {
        while (_window.isOpen() || _circleWindow.isOpen()) {
            sf::Event event;

			// Event handling for the grid window
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    _window.close();
            }

			// Event handling for the circle window
            while (_circleWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    _circleWindow.close();
            }

            sim.update();

			// Update the windows
            drawFrame(sim);
            drawCircle(sim);
        }
    }

}; // namespace km
