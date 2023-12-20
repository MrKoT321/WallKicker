#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include "map/map.h"
#include "walls/wall.h"
#include "hero/hero.h"
#include "segment/segment.h"

void initStructures(Map &map, Ground &ground, Hero &hero, HeroTextures &heroTextures, std::vector<Segment> &segments, sf::RenderWindow &window)
{
    initMap(map);
    initGround(ground);
    initHero(hero, heroTextures);
    initSegments(segments, window);
}

void pollEvents(sf::RenderWindow &window, Hero &hero, HeroTextures &heroTextures)
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
                updateHeroSprite(hero, heroTextures);
            }
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space)
            {
                updateJumpHeroState(hero);
                updateHeroSprite(hero, heroTextures);
            }
            break;
        default:
            break;
        }
    }
}

void updateScreen(sf::Vector2u windowSize, Hero &hero, std::vector<Segment> &segments, Ground &ground, float dt)
{
    const float positionToChangeScreen = windowSize.y * 0.4;
    if (hero.position.y < positionToChangeScreen)
    {
        const int screenChangeSpeed = 200;
        updateHeroPositionWithScreenMove(hero, screenChangeSpeed, dt);
        updateGroundPositionWithScreenMove(ground, screenChangeSpeed, dt);
        updateSegmentPositionWithScreenMove(segments, screenChangeSpeed, dt);
    }
}

void updateWalls(std::vector<Segment> &segments, sf::RenderWindow &window)
{
    if (isPrevSegmentEnded(segments, window))
        initNextSegment(segments, window);
}

void updateCheckpoints(std::vector<Segment> &segments, Hero &hero)
{
    if (isCurrSegmentCompleted(segments, hero.position.y))
        updateSegmentWithLvlComplete(segments);
}

void update(Hero &hero, HeroTextures &heroTextures, std::vector<Segment> &segments, sf::RenderWindow &window, Ground &ground, float dt)
{
    const sf::Vector2u windowSize = window.getSize();
    if (hero.isAlive)
    {
        std::vector<Wall> walls = getAllWalls(segments);
        updateScreen(windowSize, hero, segments, ground, dt);
        updateWalls(segments, window);
        updateHeroPosition(hero, heroTextures, walls, dt);
        updateCheckpoints(segments, hero);
    }
    if (hero.position.y + 100 > windowSize.y)
    {
        hero.isAlive = false;
    }
}

void redrawFrame(sf::RenderWindow &window, Map map, Ground ground, Hero hero, std::vector<Segment> &segments)
{
    window.clear();
    window.draw(map.img);
    drawWalls(window, segments);
    drawGround(window, ground);
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
    HeroTextures heroTextures;
    std::vector<Segment> segments;
    segments.push_back(Segment());
    segments.push_back(Segment());

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Wall Kicker", sf::Style::Default, settings);

    initStructures(map, ground, hero, heroTextures, segments, window);

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();

        pollEvents(window, hero, heroTextures);
        update(hero, heroTextures, segments, window, ground, dt);
        redrawFrame(window, map, ground, hero, segments);
    }
}