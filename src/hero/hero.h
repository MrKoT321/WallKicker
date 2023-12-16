#pragma once

struct Hero
{
    int jumpState;
    char direction;
    bool isAlive;
    float speedX = 300;
    float speedY = 500;
    sf::Sprite img;
    sf::Texture texture;
    sf::Vector2f position;
};

void initHeroTexture(sf::Texture &texture)
{
    if (!texture.loadFromFile("../images/hero/hero_stand.png"))
    {
        // error...
        std::cout << "Fail to load image" << std::endl;
        return;
    }
}

void initHero(Hero &hero)
{
    hero.jumpState = 0;
    hero.direction = 'l';
    hero.isAlive = true;
    hero.position = {473, 633};
    initHeroTexture(hero.texture);
    hero.img.setTexture(hero.texture);
    hero.img.setPosition(hero.position);
}

void updateHeroPosition(Hero &hero, std::vector<Wall> walls, float dt)
{
    const int gravity = 30;
    if (hero.jumpState == 1 || hero.jumpState == 3)
    {
        if (hero.direction == 'l')
            hero.position += {-hero.speedX * dt, -hero.speedY * dt};
        else
            hero.position += {hero.speedX * dt, -hero.speedY * dt};
        hero.speedY -= gravity;
    }
    if (hero.jumpState == 2 || hero.jumpState == 4)
    {
        if (hero.speedY > 0)
            hero.speedY = 0;
        if (hero.direction == 'l')
            hero.position += {-hero.speedX * dt, -hero.speedY * dt};
        else
            hero.position += {hero.speedX * dt, -hero.speedY * dt};
        hero.speedY -= gravity;
    }
    if (hero.jumpState == 7)
    {
        hero.position += {0, hero.speedX * dt};
    }
    if (hero.jumpState == 5 || hero.jumpState == 6)
    {
        hero.position += {0, 40 * dt};
    }
    if (hero.jumpState != 0 && hero.jumpState != 5 && hero.jumpState != 6)
    {
        const int heroWidth = 54;
        const int heroHeigth = 97;
        const int wallWidth = 20;
        const int oneWallHeigth = 80;
        const int wallsCount = (int)walls.size();
        for (int i = 0; i < wallsCount; i++)
        {
            if (hero.position.x + heroWidth >= walls[i].position.x && hero.position.x < walls[i].position.x + wallWidth &&
                hero.position.y + heroHeigth >= walls[i].position.y && (hero.position.y < walls[i].position.y + (oneWallHeigth * walls[i].size)))
            {
                if (hero.jumpState == 1 || hero.jumpState == 3)
                    hero.jumpState = 6;
                if (hero.jumpState == 2 || hero.jumpState == 4)
                    hero.jumpState = 5;
                if (hero.direction == 'l')
                    hero.direction = 'r';
                else
                    hero.direction = 'l';
            }
        }
    }
}

void updateHeroPositionWithScreenMove(Hero &hero, int screenChangeSpeed, float dt)
{
    hero.position += {0, screenChangeSpeed * dt};
}

void updateJumpHeroState(Hero &hero)
{
    const float startSpeedY = 500;
    if (hero.jumpState == 0 || hero.jumpState == 5)
    {
        hero.jumpState = 1;
        hero.speedY = startSpeedY;
    }
    if (hero.jumpState == 2)
    {
        hero.speedY = startSpeedY;
        hero.jumpState = 3;
        if (hero.direction == 'l')
            hero.direction = 'r';
        else
            hero.direction = 'l';
    }
}

void stopHeroJump(Hero &hero)
{
    if (hero.jumpState == 1)
        hero.jumpState = 2;
    if (hero.jumpState == 3)
        hero.jumpState = 4;
    if (hero.jumpState == 6)
        hero.jumpState = 5;
}