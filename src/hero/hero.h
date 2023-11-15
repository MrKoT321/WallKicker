#pragma once

struct Hero
{
    int jumpState;
    char direction;
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
    hero.position = {473, 633};
    initHeroTexture(hero.texture);
    hero.img.setTexture(hero.texture);
    hero.img.setPosition(hero.position);
}

void updateHeroPosition(Hero &hero, std::vector<Wall> walls, float dt)
{
    std::cout << hero.jumpState << " - " << hero.direction << std::endl;
    if (hero.jumpState == 1 || hero.jumpState == 3)
    {
        if (hero.direction == 'l')
            hero.position += {-100 * dt, -100 * dt};
        else
            hero.position += {100 * dt, -100 * dt};
    }
    if (hero.jumpState == 2 || hero.jumpState == 4)
    {
        if (hero.direction == 'l')
            hero.position += {-100 * dt, 100 * dt};
        else
            hero.position += {100 * dt, 100 * dt};
    }
    if (hero.jumpState == 5)
    {
        hero.position += {0, 10 * dt};
    }
    if (hero.jumpState != 5 && hero.jumpState != 0)
    {
        const int wallsCount = (int)walls.size();
        const int heroWidth = 54;
        const int wallWidth = 20;
        for (int i = 0; i < wallsCount; i++)
        {
            if (hero.position.x + heroWidth >= walls[i].position.x && hero.position.x < walls[i].position.x + wallWidth)
            {
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
}