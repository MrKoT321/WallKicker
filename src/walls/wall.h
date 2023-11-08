#pragma once

struct Wall
{
    int size;
    char type;
    sf::Sprite img;
    sf::Texture texture;
    sf::Vector2f position;
};

void initWalls(std::vector<Wall> &walls, int countWalls, std::vector<sf::Vector2f> wallsPositions, std::vector<char> wallsTypes, std::vector<int> wallsSize)
{
    for (int i = 0; i < countWalls; i++)
    {
        if (!walls[i].texture.loadFromFile("../images/walls/" + std::to_string(wallsSize[i]) + "_wall.png"))
        {
            // error...
            std::cout << "Fail to load image" << std::endl;
            return;
        }
        walls[i].img.setTexture(walls[i].texture);
        walls[i].position = wallsPositions[i];
        walls[i].img.setPosition(wallsPositions[i]);
    }
}