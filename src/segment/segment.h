#pragma once

struct Segment
{
    const int maxWallCountOnLevel = 15;
    Wall startCheckpoint;
    Wall endCheckpoint;
    char startCheckpointDir;
    char endCheckpointDir;
    std::vector<Wall> walls;
};

void initSegments(std::vector<Segment> &segments)
{
    const int countWallsLvl1 = 2;
    for (int i = 0; i < countWallsLvl1; i++)
        segments[0].walls.push_back(Wall());
    const std::vector<sf::Vector2f> wallsPosition = {{345, 0}, {635, 0}};
    const std::vector<char> wallsTypes = {'_', '_'};
    const std::vector<int> wallsSize = {10, 10};
    segments[0].startCheckpointDir = 'l';
    segments[0].endCheckpointDir = 'l';
    initWalls(segments[0].walls, countWallsLvl1, wallsPosition, wallsTypes, wallsSize);
}

void drawWalls(sf::RenderWindow &window, std::vector<Segment> &segments)
{
    const int segmentCount = (int)segments.size();
    for (int i = 0; i < segmentCount; i++)
    {
        int wallsCountOfSegment = (int)segments[i].walls.size();
        for (int j = 0; j < wallsCountOfSegment; j++)
        {
            window.draw(segments[i].walls[j].img);
        }
    }
}