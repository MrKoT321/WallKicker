#pragma once

struct Hero
{
    int jumpState;
    char direction;
    bool isAlive;
    bool isExploded;
    float speedX = 300;
    float speedY;
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
    sf::Texture hookTexture;
    sf::Texture explodeTexture;
};

char heroDirectionLeft()
{
    return 'l';
}

char heroDirectionRight()
{
    return 'r';
}

int heroStartJumpState()
{
    return 0;
}

int heroJumpJumpState()
{
    return 1;
}

int heroJumpFallJumpState()
{
    return 2;
}

int heroDoubleJumpJumpState()
{
    return 3;
}

int heroDoubleJumpFallJumpState()
{
    return 4;
}

int heroOnTheWallReadyToJumpJumpState()
{
    return 5;
}

int heroOnTheWallNotReadyToJumpJumpState()
{
    return 6;
}

int heroOnCheckpointNotReadyToJumpJumpState()
{
    return 8;
}

int heroOnCheckpointReadyToJumpJumpState()
{
    return 9;
}

int heroBouncedJumpState()
{
    return 10;
}

bool isHeroOnWall(Hero &hero)
{
    return hero.jumpState == heroOnTheWallReadyToJumpJumpState() ||
           hero.jumpState == heroOnTheWallNotReadyToJumpJumpState() ||
           hero.jumpState == heroOnCheckpointNotReadyToJumpJumpState() ||
           hero.jumpState == heroOnCheckpointReadyToJumpJumpState();
}

bool isHeroAlive(Hero &hero)
{
    return hero.isAlive;
}

bool isHeroExploded(Hero &hero)
{
    return hero.isExploded;
}

bool isHeroMovedLeft(Hero &hero)
{
    return hero.direction == heroDirectionLeft();
}

bool isHeroShouldDead(sf::Vector2u windowSize, Hero &hero)
{
    /* To see explode */
    const int deltaHeroPosition = 80;
    return hero.position.y + deltaHeroPosition > windowSize.y;
}

bool isHeroTouchesWall(sf::Vector2f heroPosition, sf::Vector2f wallPosition, int wallWidth, int wallSize)
{
    const int oneWallHeigth = 80;
    const int heroHeigth = 97;
    return heroPosition.x >= wallPosition.x &&
           heroPosition.x < wallPosition.x + wallWidth &&
           heroPosition.y + heroHeigth * 3 / 4 >= wallPosition.y &&
           heroPosition.y + heroHeigth * 1 / 4 < wallPosition.y + oneWallHeigth * wallSize;
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
    hero.jumpState = heroStartJumpState();
    hero.direction = heroDirectionLeft();
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
    if (hero.direction == heroDirectionLeft())
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
    if (hero.jumpState == heroJumpJumpState() || hero.jumpState == heroDoubleJumpJumpState() || hero.jumpState == heroBouncedJumpState())
    {
        if (hero.speedY >= 0)
            hero.img.setTexture(heroTextures.jumpTexture);
        else
            hero.img.setTexture(heroTextures.fallTexture);
    }
    if (hero.jumpState == heroJumpFallJumpState() || hero.jumpState == heroDoubleJumpFallJumpState())
        hero.img.setTexture(heroTextures.fallTexture);
    if (isHeroOnWall(hero))
        hero.img.setTexture(heroTextures.hookTexture);
}

void updateHeroImgScale(Hero &hero)
{
    const int heroWidth = 54;
    if (hero.direction == heroDirectionRight())
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
    const int defaultSliceOnWall = 40;
    if (hero.jumpState == heroJumpJumpState() || hero.jumpState == heroDoubleJumpJumpState() || hero.jumpState == heroBouncedJumpState())
    {
        if (hero.direction == heroDirectionLeft())
            hero.position += {-hero.speedX * dt, -hero.speedY * dt};
        else
            hero.position += {hero.speedX * dt, -hero.speedY * dt};
        hero.speedY -= gravity * dt;
    }
    if (hero.jumpState == heroJumpFallJumpState() || hero.jumpState == heroDoubleJumpFallJumpState())
    {
        if (hero.speedY > 0)
            hero.speedY = 0;
        if (hero.direction == heroDirectionLeft())
            hero.position += {-hero.speedX * dt, -hero.speedY * dt};
        else
            hero.position += {hero.speedX * dt, -hero.speedY * dt};
        hero.speedY -= gravity * dt;
    }
    if (hero.jumpState == heroOnTheWallReadyToJumpJumpState() || hero.jumpState == heroOnTheWallNotReadyToJumpJumpState())
    {
        hero.position += {0, defaultSliceOnWall * dt};
    }
    if (!isHeroOnWall(hero))
    {
        std::vector<Wall> walls(wallsSegment1);
        walls.insert(walls.end(), wallsSegment2.begin(), wallsSegment2.end());
        const int wallsCount = (int)walls.size();
        for (int i = 0; i < wallsCount; i++)
        {
            if (isHeroTouchesWall(hero.position, getWallPosition(walls[i]), getWallWidth(walls[i]), getWallSize(walls[i])))
            {
                if (isHeroOnSpikeWall(walls[i], isHeroMovedLeft(hero)))
                {
                    setHeroAlive(hero, false);
                    setHeroExploded(hero, true);
                    normolizeHeroExplodePosition(hero);
                    return 0;
                }
                if (hero.jumpState == heroJumpJumpState() || hero.jumpState == heroDoubleJumpJumpState())
                    hero.jumpState = heroOnTheWallNotReadyToJumpJumpState();
                if (hero.jumpState == heroJumpFallJumpState() || hero.jumpState == heroDoubleJumpFallJumpState())
                    hero.jumpState = heroOnTheWallReadyToJumpJumpState();
                if (i == (int)wallsSegment1.size() - 1 || i == (int)walls.size() - 1)
                {
                    if (hero.jumpState == heroOnTheWallNotReadyToJumpJumpState())
                        hero.jumpState = heroOnCheckpointNotReadyToJumpJumpState();
                    else
                        hero.jumpState = heroOnCheckpointReadyToJumpJumpState();
                }
                if (hero.direction == heroDirectionLeft())
                    hero.direction = heroDirectionRight();
                else
                    hero.direction = heroDirectionLeft();
                if (isHeroOnBounceWall(walls[i]))
                {
                    hero.jumpState = heroBouncedJumpState();
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
    if (hero.jumpState == heroStartJumpState() ||
        hero.jumpState == heroOnTheWallReadyToJumpJumpState() ||
        hero.jumpState == heroOnCheckpointReadyToJumpJumpState())
    {
        hero.jumpState = heroJumpJumpState();
        heroStartJump(hero);
        updateHeroImgScale(hero);
    }
    if (hero.jumpState == heroJumpFallJumpState() || hero.jumpState == heroBouncedJumpState())
    {
        heroStartJump(hero);
        hero.jumpState = heroDoubleJumpJumpState();
        if (hero.direction == heroDirectionLeft())
            hero.direction = heroDirectionRight();
        else
            hero.direction = heroDirectionLeft();
        updateHeroImgScale(hero);
    }
}

void stopHeroJump(Hero &hero)
{
    if (hero.jumpState == heroJumpJumpState())
        hero.jumpState = heroJumpFallJumpState();
    if (hero.jumpState == heroDoubleJumpJumpState())
        hero.jumpState = heroDoubleJumpFallJumpState();
    if (hero.jumpState == heroOnTheWallNotReadyToJumpJumpState())
        hero.jumpState = heroOnTheWallReadyToJumpJumpState();
    if (hero.jumpState == heroOnCheckpointNotReadyToJumpJumpState())
        hero.jumpState = heroOnCheckpointReadyToJumpJumpState();
}

sf::Vector2f getHeroPosition(Hero &hero)
{
    return hero.position;
}