#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void pollEvents(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window)
{
    window.clear();
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
            "Wall Kicker", sf::Style::Default, settings);

    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window);
    }
}