#pragma once

struct Game
{
    int score;
    bool isRestart;
    sf::Font scoreFont;
    sf::Vector2f scorePosition;
    sf::Text scoreText;
};

bool isGameRestarted(Game &game)
{
    return game.isRestart;
}

void initScoreFont(Game &game)
{
    if (!game.scoreFont.loadFromFile("./game/arial.ttf"))
    {
        std::cout << "Fail to load score font" << std::endl;
    }
}

void initScoreTextStyles(Game &game)
{
    const sf::Vector2f intDefaultScoreTextPosition = {10, 10};
    const int defaultScoreTextSize = 35;
    game.scorePosition = intDefaultScoreTextPosition;
    game.scoreText.setCharacterSize(defaultScoreTextSize);
    game.scoreText.setFillColor(sf::Color::Black);
    game.scoreText.setFont(game.scoreFont);
}

void initGame(Game &game)
{
    game.score = 0;
    game.isRestart = false;
    initScoreFont(game);
    initScoreTextStyles(game);
}

void drawScore(sf::RenderWindow &window, Game &game)
{
    std::ostringstream oss;
    oss << "SCORE: " << game.score;
    game.scoreText.setPosition(game.scorePosition);
    game.scoreText.setString(oss.str());
    window.draw(game.scoreText);
}

void drawScoreEndGame(sf::RenderWindow &window, Game &game)
{
    const sf::Vector2f defaultScoreTextEndGamePosition = {660, 400};
    const int defaultScoreTextEndGameSize = 70;
    std::ostringstream oss;
    oss << "" << game.score;
    game.scorePosition = defaultScoreTextEndGamePosition;
    game.scoreText.setCharacterSize(defaultScoreTextEndGameSize);
    game.scoreText.setFillColor(sf::Color::White);
    game.scoreText.setPosition(game.scorePosition);
    game.scoreText.setString(oss.str());
    window.draw(game.scoreText);
}

void restartGame(Game &game, Hero &hero)
{
    if (!isHeroAlive(hero) && !isHeroExploded(hero))
        game.isRestart = true;
}

void increaseGameScore(Game &game)
{
    game.score += 1;
}