#pragma once

struct Wall
{
    int size;
    char type;
    sf::Sprite img;
    sf::Texture texture;
    sf::Vector2f position;
};

void initWalls(std::vector<Wall> &walls, int countWalls, std::vector<sf::Vector2f> wallsPositions, std::vector<std::string> wallsTypes, std::vector<int> wallsSize)
{
    for (int i = 0; i < countWalls; i++)
    {
        if (!walls[i].texture.loadFromFile("../images/walls/" + std::to_string(wallsSize[i]) + wallsTypes[i] + ".png"))
        {
            // error...
            std::cout << "Fail to load image" << std::endl;
            return;
        }
        walls[i].img.setTexture(walls[i].texture);
        walls[i].position = wallsPositions[i];
        walls[i].img.setPosition(wallsPositions[i]);
        walls[i].size = wallsSize[i];
        std::cout << walls[i].position.y << std::endl;
    }
}

void initWallsNextSegment(std::vector<Wall> &walls, float lvl2SegmentStart, int countWalls, std::vector<sf::Vector2f> wallsPositions, std::vector<std::string> wallsTypes, std::vector<int> wallsSize)
{
    for (int i = 0; i < countWalls; i++)
    {
        if (!walls[i].texture.loadFromFile("../images/walls/" + std::to_string(wallsSize[i]) + wallsTypes[i] + ".png"))
        {
            // error...
            std::cout << "Fail to load image" << std::endl;
            return;
        }
        wallsPositions[i].y += lvl2SegmentStart;
        walls[i].img.setTexture(walls[i].texture);
        walls[i].position = wallsPositions[i];
        walls[i].img.setPosition(wallsPositions[i]);
        walls[i].size = wallsSize[i];
        std::cout << walls[i].position.y << std::endl;
    }
}