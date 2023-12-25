#pragma once

struct Hero
{
    int jumpState;
    char direction;
    bool isAlive;
    float speedX = 300;
    float speedY = 500;
    sf::Sprite img;
    sf::Vector2f position;
};

struct HeroTextures
{
    sf::Texture standTexture;
    sf::Texture jumpTexture;
    sf::Texture fallTexture;
    sf::Texture startFlipTexture1;
    sf::Texture startFlipTexture2;
    sf::Texture flipTexture1;
    sf::Texture flipTexture2;
    sf::Texture flipTexture3;
    sf::Texture hookTexture;
};

struct HeroExplodeSprite
{
    sf::Texture explodeTexture1;
    sf::Texture explodeTexture2;
    sf::Texture explodeTexture3;
};

void initHeroTexture(HeroTextures &heroTextures)
{
    if (!heroTextures.standTexture.loadFromFile("../images/hero/hero_stand.png"))
    {
        std::cout << "Fail to load stand image" << std::endl;
    }
    if (!heroTextures.jumpTexture.loadFromFile("../images/hero/hero_jump.png"))
    {
        std::cout << "Fail to load jump image" << std::endl;
    }
    if (!heroTextures.fallTexture.loadFromFile("../images/hero/hero_fall.png"))
    {
        std::cout << "Fail to load fall image" << std::endl;
    }
    if (!heroTextures.startFlipTexture1.loadFromFile("../images/hero/hero_start_flip1.png"))
    {
        std::cout << "Fail to load start flip 1 image" << std::endl;
    }
    if (!heroTextures.startFlipTexture2.loadFromFile("../images/hero/hero_start_flip2.png"))
    {
        std::cout << "Fail to load start flip 2 image" << std::endl;
    }
    if (!heroTextures.flipTexture1.loadFromFile("../images/hero/hero_flip1.png"))
    {
        std::cout << "Fail to load flip 1 image" << std::endl;
    }
    if (!heroTextures.flipTexture2.loadFromFile("../images/hero/hero_flip2.png"))
    {
        std::cout << "Fail to load flip 2 image" << std::endl;
    }
    if (!heroTextures.flipTexture3.loadFromFile("../images/hero/hero_flip3.png"))
    {
        std::cout << "Fail to load flip 3 image" << std::endl;
    }
    if (!heroTextures.hookTexture.loadFromFile("../images/hero/hero_hook.png"))
    {
        std::cout << "Fail to load hook image" << std::endl;
    }
}

void initHero(Hero &hero, HeroTextures &heroTextures)
{
    hero.jumpState = 0;
    hero.direction = 'l';
    hero.isAlive = true;
    hero.position = {473, 633};
    initHeroTexture(heroTextures);
    hero.img.setTexture(heroTextures.standTexture);
    hero.img.setPosition(hero.position);
}

bool isHeroOnWall(Hero &hero)
{
    return hero.jumpState == 5 || hero.jumpState == 6 || hero.jumpState == 8 || hero.jumpState == 9;
}

void updateHeroSprite(Hero &hero, HeroTextures &heroTextures)
{
    if (hero.jumpState == 1)
    {
        if (hero.speedY >= 0)
        {
            hero.img.setTexture(heroTextures.jumpTexture);
        }
        else
        {
            hero.img.setTexture(heroTextures.fallTexture);
        }
    }
    if (hero.jumpState == 2)
        hero.img.setTexture(heroTextures.fallTexture);
    if (isHeroOnWall(hero))
        hero.img.setTexture(heroTextures.hookTexture);
}

void updateHeroImgScale(Hero &hero)
{
    const int heroWidth = 54;
    if (hero.direction == 'r')
    {
        hero.img.setScale(-1, 1);
        hero.position.x += heroWidth;
    }
    else
    {
        hero.img.setScale(1, 1);
        hero.position.x -= heroWidth;
    }
}

void updateHeroPosition(Hero &hero, HeroTextures &heroTextures, std::vector<Wall> wallsSegment1, std::vector<Wall> wallsSegment2, float dt)
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
    if (hero.jumpState == 5 || hero.jumpState == 6)
    {
        hero.position += {0, 40 * dt};
    }
    if (hero.jumpState == 7)
    {
        hero.position += {0, hero.speedX * dt};
    }
    if (!isHeroOnWall(hero))
    {
        const int heroWidth = 54;
        const int heroHeigth = 97;
        const int wallWidth = 20;
        const int oneWallHeigth = 80;
        std::vector<Wall> walls(wallsSegment1);
        walls.insert(walls.end(), wallsSegment2.begin(), wallsSegment2.end());
        const int wallsCount = (int)walls.size();
        for (int i = 0; i < wallsCount; i++)
        {
            if (hero.position.x >= walls[i].position.x && hero.position.x < walls[i].position.x + wallWidth &&
                hero.position.y + heroHeigth * 3 / 4 >= walls[i].position.y && hero.position.y + heroHeigth * 1 / 4 < walls[i].position.y + oneWallHeigth * walls[i].size)
            {
                if (hero.jumpState == 1 || hero.jumpState == 3)
                    hero.jumpState = 6;
                if (hero.jumpState == 2 || hero.jumpState == 4)
                    hero.jumpState = 5;
                if (i == (int)wallsSegment1.size() - 1 || i == (int)wallsSegment2.size() - 1)
                {
                    if (hero.jumpState == 6)
                        hero.jumpState = 8;
                    else
                        hero.jumpState = 9;
                }
                if (hero.direction == 'l')
                    hero.direction = 'r';
                else
                    hero.direction = 'l';
                updateHeroSprite(hero, heroTextures);
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
    if (hero.jumpState == 0 || hero.jumpState == 5 || hero.jumpState == 9)
    {
        hero.jumpState = 1;
        hero.speedY = startSpeedY;
        updateHeroImgScale(hero);
    }
    if (hero.jumpState == 2)
    {
        hero.speedY = startSpeedY;
        hero.jumpState = 3;
        if (hero.direction == 'l')
            hero.direction = 'r';
        else
            hero.direction = 'l';
        updateHeroImgScale(hero);
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
    if (hero.jumpState == 8)
        hero.jumpState = 9;
}

void setHeroDead(Hero &hero)
{
    hero.isAlive = false;
}

bool isHeroAlive(Hero hero)
{
    return hero.isAlive;
}

bool isHeroDead(sf::Vector2u windowSize, Hero hero)
{
    return hero.position.y + 100 > windowSize.y;
}