#pragma once

struct Map
{
    sf::Texture texture;
    sf::Sprite img;
};

struct Ground
{
    sf::Texture texture;
    sf::Sprite img;
    sf::Vector2f position;
};

void initMapTexture(sf::Texture &texture)
{
    if (!texture.loadFromFile("../images/map/background.png"))
    {
        // error...
        std::cout << "Fail to load image" << std::endl;
        return;
    }
}

void initGroundTexture(sf::Texture &texture)
{
    if (!texture.loadFromFile("../images/map/ground.png"))
    {
        // error...
        std::cout << "Fail to load image" << std::endl;
        return;
    }
}

initMap(Map &map)
{
    initMapTexture(map.texture);
    map.img.setTexture(map.texture);
}

initGround(Ground &ground)
{
    ground.position = {0, 724};
    initGroundTexture(ground.texture);
    ground.img.setTexture(ground.texture);
    ground.img.setPosition(ground.position);
}

drawGround(sf::RenderWindow &window, Ground &ground)
{
    ground.img.setPosition(ground.position);
    window.draw(ground.img);
}