#pragma once

struct Wall
{
    const int WIDTH = 20;
    int size;
    char type;
    sf::Sprite img;
    sf::Texture texture;
    sf::Vector2f position;
};

void initWallsTexture(sf::Texture texture[], int wallsSize[], int LEN_WALLS_ARRAY)
{
    for (int i = 0; i < LEN_WALLS_ARRAY; i++)
    {
        if (!texture[i].loadFromFile("../images/walls/" + std::to_string(wallsSize[i]) + "_wall.png"))
        {
            // error...
            std::cout << "Fail to load image" << std::endl;
            return;
        }
    }
}

void setWallsTexture(sf::Sprite walls[], sf::Texture texture[], int LEN_WALLS_ARRAY)
{
    for (int i = 0; i < LEN_WALLS_ARRAY; i++)
    {
        walls[i].setTexture(texture[i]);
    }
}

void setWallsPosition(sf::Sprite walls[], sf::Vector2f wallsPosition[], int LEN_WALLS_ARRAY)
{
    for (int i = 0; i < LEN_WALLS_ARRAY; i++)
    {
        walls[i].setPosition(wallsPosition[i]);
    }
}

void drawWalls(sf::RenderWindow &window, sf::Sprite walls[], int LEN_WALLS_ARRAY)
{
    for (int i = 0; i < LEN_WALLS_ARRAY; i++)
    {
        window.draw(walls[i]);
    }
}

void drawWalls(sf::RenderWindow &window)
{
    const int LEN_WALLS_ARRAY = 2;
    int wallsSize[LEN_WALLS_ARRAY]{10, 10};
    sf::Vector2f wallsPosition[LEN_WALLS_ARRAY]{
        {345, 0}, {635, 0}};
    sf::Sprite walls[LEN_WALLS_ARRAY];
    sf::Texture texture[LEN_WALLS_ARRAY];
    initWallsTexture(texture, wallsSize, LEN_WALLS_ARRAY);
    setWallsTexture(walls, texture, LEN_WALLS_ARRAY);
    setWallsPosition(walls, wallsPosition, LEN_WALLS_ARRAY);
    drawWalls(window, walls, LEN_WALLS_ARRAY);
}

void initWalls(Wall walls[], int countWalls, sf::Vector2f wallsPositions[], char wallsTypes[], int wallsSize[])
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