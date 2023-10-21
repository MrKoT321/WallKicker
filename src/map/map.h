#pragma once

void initTexture(sf::Texture &texture)
{
    if (!texture.loadFromFile("../images/map/map.png"))
    {
        // error...
        std::cout << "Fail to load image" << std::endl;
        return;
    }
}

void renderMap(sf::RenderWindow &window)
{
    sf::Sprite map;
    sf::Texture texture;
    initTexture(texture);
    map.setTexture(texture);
    window.draw(map);
}