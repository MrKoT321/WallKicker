#pragma once

struct Wall
{
    int size;
    char feature;
    sf::Sprite img;
    sf::Texture texture;
    sf::Vector2f position;
};

void initWallsSegment(std::vector<Wall> &walls, int countWalls, std::vector<sf::Vector2f> wallsPositions, std::vector<std::string> wallsTypes, std::vector<int> wallsSize, std::vector<char> wallsFeature, float segmentStart = 0)
{
    for (int i = 0; i < countWalls; i++)
    {
        if (!walls[i].texture.loadFromFile("../images/walls/" + std::to_string(wallsSize[i]) + wallsTypes[i] + ".png"))
        {
            std::cout << "Fail to load image" << std::endl;
            return;
        }
        wallsPositions[i].y += segmentStart;
        walls[i].img.setTexture(walls[i].texture);
        walls[i].position = wallsPositions[i];
        walls[i].img.setPosition(wallsPositions[i]);
        walls[i].size = wallsSize[i];
        walls[i].feature = wallsFeature[i];
    }
}

void updateCheckpointImgWithLvlComplete(Wall &wall)
{
    if (!wall.texture.loadFromFile("../images/walls/1_checkpoint_active.png"))
    {
        std::cout << "Fail to load image" << std::endl;
        return;
    }
    wall.img.setTexture(wall.texture);
}

bool isHeroOnSpike(Wall wall, char heroDirection)
{
    if (wall.feature == 's' || wall.feature == 'c')
        return false;
    if (wall.feature == 'b')
        return true;
    if (wall.feature == 'l' && heroDirection == 'r')
        return true;
    if (wall.feature == 'r' && heroDirection == 'l')
        return true;
    return false;
}

std::string getSimpleWallType()
{
    return "_wall";
}

std::string getEnableCheckpointWallType()
{
    return "_checkpoint_enabled";
}

std::string getLeftSpikeWallType()
{
    return "_spike_left";
}

std::string getRightSpikeWallType()
{
    return "_spike_right";
}

std::string getBothSpikeWallType()
{
    return "_spike_both";
}

char getSimpleWallFeature()
{
    return 's';
}

char getCheckpointWallFeature()
{
    return 'c';
}

char getLeftSpikeWallFeature()
{
    return 'l';
}

char getRightSpikeWallFeature()
{
    return 'r';
}

char getBothSpikeWallFeature()
{
    return 'b';
}