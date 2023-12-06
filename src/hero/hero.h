#pragma once

struct Hero
{
    int jumpState;
    char direction;
    bool isAlive;
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
    const int wallsCount = (int)walls.size();
    const int oneWallHeigth = 80;
    if (hero.jumpState == 1 || hero.jumpState == 3)
    {
        if (hero.direction == 'l')
            hero.position += {-120 * dt, -200 * dt};
        else
            hero.position += {120 * dt, -200 * dt};
    }
    if (hero.jumpState == 2 || hero.jumpState == 4)
    {
        if (hero.direction == 'l')
            hero.position += {-120 * dt, 200 * dt};
        else
            hero.position += {120 * dt, 200 * dt};
    }
    if (hero.jumpState == 7)
    {
        hero.position += {0, 120 * dt};
    }
    if (hero.jumpState == 5 || hero.jumpState == 6)
    {
        hero.position += {0, 40 * dt};
    }
    if (hero.jumpState != 0 && hero.jumpState != 5 && hero.jumpState != 6)
    {
        const int heroWidth = 54;
        const int wallWidth = 20;
        const bool sos = hero.position.y > walls[0].position.y;
        const bool gai = hero.position.y < walls[0].position.y + oneWallHeigth * walls[0].size;
        for (int i = 0; i < wallsCount; i++)
        {
            if (hero.position.x + heroWidth >= walls[i].position.x && hero.position.x < walls[i].position.x + wallWidth &&
                hero.position.y > walls[i].position.y && hero.position.y < walls[i].position.y + oneWallHeigth * walls[i].size)
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

void updateJumpHeroState(Hero &hero)
{
    if (hero.jumpState == 0 || hero.jumpState == 5)
    {
        hero.jumpState = 1;
    }
    if (hero.jumpState == 2)
    {
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