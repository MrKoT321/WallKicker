#pragma once

struct Hero
{
    int jumpState;
    char direction;
    bool isAlive;
    bool isExploded;
    float speedX = 300;
    float speedY = 500;
    sf::Vector2f position;
    sf::Sprite img;
    sf::Sprite explodeImg;
};

struct HeroTextures
{
    float spriteTime;
    sf::Texture standTexture;
    sf::Texture jumpTexture;
    sf::Texture fallTexture;
    sf::Texture startFlipTexture1;
    sf::Texture startFlipTexture2;
    sf::Texture flipTexture1;
    sf::Texture flipTexture2;
    sf::Texture flipTexture3;
    sf::Texture hookTexture;
    sf::Texture explodeTexture;
};

bool isHeroOnWall(Hero &hero)
{
    return hero.jumpState == 5 || hero.jumpState == 6 || hero.jumpState == 8 || hero.jumpState == 9;
}

bool isHeroAlive(Hero &hero)
{
    return hero.isAlive;
}

bool isHeroExploded(Hero &hero)
{
    return hero.isExploded;
}

bool isHeroShouldDead(sf::Vector2u windowSize, Hero &hero)
{
    return hero.position.y + 80 > windowSize.y;
}

void setHeroAlive(Hero &hero, bool state)
{
    hero.isAlive = state;
}

void setHeroExploded(Hero &hero, bool state)
{
    hero.isExploded = state;
}

void initHeroTexture(HeroTextures &heroTextures)
{
    heroTextures.spriteTime = 0;
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
    if (!heroTextures.explodeTexture.loadFromFile("../images/hero/hero_explode_sprites.png"))
    {
        std::cout << "Fail to load explode image" << std::endl;
    }
}

void initHero(Hero &hero, HeroTextures &heroTextures)
{
    hero.jumpState = 0;
    hero.direction = 'l';
    hero.isExploded = false;
    hero.isAlive = true;
    hero.position = {473, 633};
    initHeroTexture(heroTextures);
    hero.img.setTexture(heroTextures.standTexture);
    hero.img.setPosition(hero.position);
    hero.img.setScale(1, 1);
    hero.explodeImg.setTexture(heroTextures.explodeTexture);
}

void drawHero(sf::RenderWindow &window, Hero &hero)
{
    if (isHeroAlive(hero))
    {
        hero.img.setPosition(hero.position);
        window.draw(hero.img);
    }
    if (isHeroExploded(hero))
    {
        hero.explodeImg.setPosition(hero.position);
        window.draw(hero.explodeImg);
    }
}

void normolizeHeroExplodePosition(Hero &hero)
{
    const int collerateDeltaX = 25;
    const int collerateDeltaY = 10;
    if (hero.direction == 'l')
    {
        if (isHeroOnWall(hero))
            hero.position.x += collerateDeltaX;
        else
            hero.position.x -= collerateDeltaX;
    }
    else
    {
        if (isHeroOnWall(hero))
            hero.position.x -= collerateDeltaX;
        else
            hero.position.x += collerateDeltaX;
    }
    hero.position.y -= collerateDeltaY;
}

void heroExplode(sf::RenderWindow &window, Hero &hero, HeroTextures &heroTextures, float dt)
{
    heroTextures.spriteTime += dt;
    const float spriteTimeDuration = 1;
    const int spitesCount = 28;
    const int spritesInRow = 8;
    const int currSpriteIndex = std::floor(spitesCount / spriteTimeDuration * heroTextures.spriteTime);
    const int explodeSize = 100;
    const sf::Vector2u spritePosition = {(unsigned int)currSpriteIndex % spritesInRow, (unsigned int)currSpriteIndex / spritesInRow};
    hero.explodeImg.setTextureRect(sf::IntRect(spritePosition.x * explodeSize, spritePosition.y * explodeSize, explodeSize, explodeSize));
    if (currSpriteIndex > spitesCount)
        setHeroExploded(hero, false);
}

void updateHeroSprite(Hero &hero, HeroTextures &heroTextures)
{
    if (hero.jumpState == 1 || hero.jumpState == 3 || hero.jumpState == 10)
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
    if (hero.jumpState == 2 || hero.jumpState == 4)
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
        hero.explodeImg.setScale(-1, 1);
        hero.position.x += heroWidth;
    }
    else
    {
        hero.img.setScale(1, 1);
        hero.explodeImg.setScale(1, 1);
        hero.position.x -= heroWidth;
    }
}

void heroStartJump(Hero &hero)
{
    const float startSpeedY = 450;
    hero.speedY = startSpeedY;
}

float updateHeroPosition(Hero &hero, HeroTextures &heroTextures, std::vector<Wall> &wallsSegment1, std::vector<Wall> &wallsSegment2, float dt)
{
    const int gravity = 700;
    if (hero.jumpState == 1 || hero.jumpState == 3 || hero.jumpState == 10)
    {
        if (hero.direction == 'l')
            hero.position += {-hero.speedX * dt, -hero.speedY * dt};
        else
            hero.position += {hero.speedX * dt, -hero.speedY * dt};
        hero.speedY -= gravity * dt;
    }
    if (hero.jumpState == 2 || hero.jumpState == 4)
    {
        if (hero.speedY > 0)
            hero.speedY = 0;
        if (hero.direction == 'l')
            hero.position += {-hero.speedX * dt, -hero.speedY * dt};
        else
            hero.position += {hero.speedX * dt, -hero.speedY * dt};
        hero.speedY -= gravity * dt;
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
        const int oneWallHeigth = 80;
        int wallWidth;
        std::vector<Wall> walls(wallsSegment1);
        walls.insert(walls.end(), wallsSegment2.begin(), wallsSegment2.end());
        const int wallsCount = (int)walls.size();
        for (int i = 0; i < wallsCount; i++)
        {
            wallWidth = getWallWidth(walls[i]);
            if (hero.position.x >= walls[i].position.x && hero.position.x < walls[i].position.x + wallWidth &&
                hero.position.y + heroHeigth * 3 / 4 >= walls[i].position.y && hero.position.y + heroHeigth * 1 / 4 < walls[i].position.y + oneWallHeigth * walls[i].size)
            {
                if (isHeroOnSpikeWall(walls[i], hero.direction))
                {
                    setHeroAlive(hero, false);
                    setHeroExploded(hero, true);
                    normolizeHeroExplodePosition(hero);
                    return 0;
                }
                if (hero.jumpState == 1 || hero.jumpState == 3)
                    hero.jumpState = 6;
                if (hero.jumpState == 2 || hero.jumpState == 4)
                    hero.jumpState = 5;
                if (i == (int)wallsSegment1.size() - 1 || i == (int)walls.size() - 1)
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
                if (isHeroOnBounceWall(walls[i]))
                {
                    hero.jumpState = 10;
                    heroStartJump(hero);
                    updateHeroImgScale(hero);
                    return 0;
                }
                updateHeroSprite(hero, heroTextures);
            }
        }
    }
    return hero.speedY;
}

void updateHeroPositionWithScreenMove(Hero &hero, int screenChangeSpeed, float dt)
{
    hero.position += {0, screenChangeSpeed * dt};
}

void updateJumpHeroState(Hero &hero)
{
    if (hero.jumpState == 0 || hero.jumpState == 5 || hero.jumpState == 9)
    {
        hero.jumpState = 1;
        heroStartJump(hero);
        updateHeroImgScale(hero);
    }
    if (hero.jumpState == 2 || hero.jumpState == 10)
    {
        heroStartJump(hero);
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