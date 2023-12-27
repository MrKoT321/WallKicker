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
    game.scorePosition = {10, 10};
    game.scoreText.setCharacterSize(35);
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
    std::ostringstream oss;
    oss << "" << game.score;
    game.scorePosition = {600, 521};
    game.scoreText.setCharacterSize(70);
    game.scoreText.setFillColor(sf::Color::White);
    game.scoreText.setPosition(game.scorePosition);
    game.scoreText.setString(oss.str());
    window.draw(game.scoreText);
}

void restartGame(Game &game, Hero hero)
{
    if (!isHeroAlive(hero) && !isHeroExploded(hero))
        game.isRestart = true;
}

void increaseGameScore(Game &game)
{
    game.score += 1;
}