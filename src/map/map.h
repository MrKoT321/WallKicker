#pragma once

struct Map
{
    sf::Texture texture;
    sf::Texture gameOverTexture;
    sf::Sprite img;
    sf::Sprite gameOverImg;
};

struct Ground
{
    sf::Texture texture;
    sf::Sprite img;
    sf::Vector2f position;
};

void initMapTexture(Map &map)
{
    if (!map.texture.loadFromFile("../images/map/background.png"))
    {
        std::cout << "Fail to map image" << std::endl;
    }
    if (!map.gameOverTexture.loadFromFile("../images/map/game_over_screen.png"))
    {
        std::cout << "Fail to game over image" << std::endl;
    }
}

void initGroundTexture(sf::Texture &texture)
{
    if (!texture.loadFromFile("../images/map/ground.png"))
    {
        std::cout << "Fail to ground image" << std::endl;
    }
}

void initMap(Map &map)
{
    initMapTexture(map);
    map.img.setTexture(map.texture);
    map.gameOverImg.setTexture(map.gameOverTexture);
}

void drawMap(sf::RenderWindow &window, Map &map)
{
    window.draw(map.img);
}

void drawEndGameScreen(sf::RenderWindow &window, Map &map)
{
    window.draw(map.gameOverImg);
}

void initGround(Ground &ground)
{
    ground.position = {0, 724};
    initGroundTexture(ground.texture);
    ground.img.setTexture(ground.texture);
    ground.img.setPosition(ground.position);
}

void drawGround(sf::RenderWindow &window, Ground &ground)
{
    ground.img.setPosition(ground.position);
    window.draw(ground.img);
}

void updateGroundPositionWithScreenMove(Ground &ground, int screenChangeSpeed, float dt)
{
    ground.position.y += screenChangeSpeed * dt;
}