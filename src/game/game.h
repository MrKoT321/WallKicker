#pragma once

struct Game
{
    int score;
    bool isRestart;
};

void initGame(Game &game)
{
    game.score = 0;
    game.isRestart = false;
}

void restartGame(Game &game, Hero hero)
{
    if (!isHeroAlive(hero))
        game.isRestart = true;
}

bool isGameRestarted(Game game)
{
    return game.isRestart;
}