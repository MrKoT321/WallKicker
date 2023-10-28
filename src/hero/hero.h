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

void updateHeroPosition(sf::Sprite &hero, int jumpState)
{
    if (jumpState == 1)
    {
        std::cout << "jumped" << std::endl;
        sf::Vector2f heroPosition = hero.getPosition();
        heroPosition.x += 1;
        heroPosition.y += 1;
        hero.setPosition(heroPosition);
    }
    // else
    //     hero.setPosition({467, 611});
}

void initHero(Hero &hero)
{
    hero.direction = 'l';
    hero.position = {473, 633};
    initHeroTexture(hero.texture);
    hero.img.setTexture(hero.texture);
    hero.img.setPosition(hero.position);
}