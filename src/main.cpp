#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include "map/map.h"
#include "walls/wall.h"
#include "hero/hero.h"
#include "segment/segment.h"

void initStructures(Map &map, Ground &ground, Hero &hero, std::vector<Segment> &segments)
{
    initMap(map);
    initGround(ground);
    initHero(hero);
    initSegments(segments);
}

void pollEvents(sf::RenderWindow &window, Hero &hero)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::Space)
            {
                stopHeroJump(hero);
            }
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space)
            {
                updateJumpHeroState(hero);
            }
            break;
        default:
            break;
        }
    }
}

void update(Hero &hero, std::vector<Segment> &segments, float dt)
{
    if (hero.isAlive)
    {
        std::vector<Wall> walls = getAllWalls(segments);
        updateHeroPosition(hero, walls, dt);
    }
}

void redrawFrame(sf::RenderWindow &window, Map map, Ground ground, Hero hero, std::vector<Segment> &segments)
{
    window.clear();
    window.draw(map.img);
    drawWalls(window, segments);
    window.draw(ground.img);
    hero.img.setPosition(hero.position);
    window.draw(hero.img);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 1000;
    constexpr unsigned WINDOW_HEIGHT = 800;

    sf::Clock clock;
    Map map;
    Ground ground;
    Hero hero;
    std::vector<Segment> segments;
    segments.push_back(Segment());
    segments.push_back(Segment());

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Wall Kicker", sf::Style::Default, settings);

    initStructures(map, ground, hero, segments);

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();

        pollEvents(window, hero);
        update(hero, segments, dt);
        redrawFrame(window, map, ground, hero, segments);
    }
}