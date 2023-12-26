#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include "map/map.h"
#include "walls/wall.h"
#include "hero/hero.h"
#include "segment/segment.h"
#include "game/game.h"

sf::Vector2u getWindowSize(sf::RenderWindow &window)
{
    return window.getSize();
}

void initStructures(Game &game, Map &map, Ground &ground, Hero &hero, HeroTextures &heroTextures, std::vector<Segment> &segments, sf::RenderWindow &window)
{
    initGame(game);
    initMap(map);
    initGround(ground);
    initHero(hero, heroTextures);
    initSegments(segments, getWindowSize(window));
}

void pollEvents(sf::RenderWindow &window, Game &game, Hero &hero, HeroTextures &heroTextures)
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
            if (event.key.code == sf::Keyboard::Space && isHeroAlive(hero))
            {
                stopHeroJump(hero);
                updateHeroSprite(hero, heroTextures);
                break;
            }
            if (event.key.code == sf::Keyboard::Return)
                restartGame(game, hero);
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space && isHeroAlive(hero))
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
    if (isPrevSegmentEnded(segments, getWindowSize(window)))
        initNextSegment(segments, getWindowSize(window));
}

void updateCheckpoints(std::vector<Segment> &segments, Hero &hero)
{
    if (isCurrSegmentCompleted(segments, hero.position.y))
        updateSegmentWithLvlComplete(segments);
}

void update(Hero &hero, HeroTextures &heroTextures, std::vector<Segment> &segments, sf::RenderWindow &window, Ground &ground, float dt)
{
    if (isHeroAlive(hero))
    {
        updateHeroPosition(hero, heroTextures, segments[0].walls, segments[1].walls, dt);
        updateScreen(getWindowSize(window), hero, segments, ground, dt);
        updateWalls(segments, window);
        updateCheckpoints(segments, hero);
    }
    if (isHeroShouldDead(getWindowSize(window), hero) && isHeroAlive(hero))
    {
        setHeroAlive(hero, false);
        setHeroExploded(hero, true);
        normolizeHeroExplodePosition(hero);
    }
    if (isHeroExploded(hero))
    {
        heroExplode(window, hero, heroTextures, dt);
    }
}

void redrawFrame(sf::RenderWindow &window, Map map, Ground ground, Hero hero, std::vector<Segment> &segments)
{
    window.clear();
    drawMap(window, map);
    drawWalls(window, segments);
    drawGround(window, ground);
    drawHero(window, hero);
    if (!isHeroAlive(hero) && !isHeroExploded(hero))
        drawEndGameScreen(window, map);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 1000;
    constexpr unsigned WINDOW_HEIGHT = 800;

    sf::Clock clock;
    Game game;
    Map map;
    Ground ground;
    Hero hero;
    HeroTextures heroTextures;
    std::vector<Segment> segments;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Wall Kicker", sf::Style::Default, settings);

    initStructures(game, map, ground, hero, heroTextures, segments, window);

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, game, hero, heroTextures);
        update(hero, heroTextures, segments, window, ground, dt);
        redrawFrame(window, map, ground, hero, segments);
        if (isGameRestarted(game))
            initStructures(game, map, ground, hero, heroTextures, segments, window);
    }
}