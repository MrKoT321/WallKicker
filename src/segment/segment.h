#pragma once

struct Segment
{
    const int maxWallCountOnLevel = 15;
    char startCheckpointDir;
    char endCheckpointDir;
    std::vector<Wall> walls;
};

void initSegments(std::vector<Segment> &segments, sf::RenderWindow &window)
{
    const int countWallsLvl1 = 4;
    for (int i = 0; i < countWallsLvl1; i++)
        segments[0].walls.push_back(Wall());
    const std::vector<sf::Vector2f> wallsPositionLvl1 = {{345, 400}, {635, 0}, {200, 10}, {200, -120}};
    const std::vector<std::string> wallsTypesLvl1 = {"_wall", "_wall", "_wall", "_checkpoint_enabled"};
    const std::vector<int> wallsSizeLvl1 = {5, 10, 3, 1};
    segments[0].startCheckpointDir = 'l';
    segments[0].endCheckpointDir = 'r';
    initWalls(segments[0].walls, countWallsLvl1, wallsPositionLvl1, wallsTypesLvl1, wallsSizeLvl1);

    const int countWallsLvl2 = 4;
    const sf::Vector2u windowSize = window.getSize();
    for (int i = 0; i < countWallsLvl2; i++)
        segments[1].walls.push_back(Wall());
    const float lvl2SegmentStart = wallsPositionLvl1[countWallsLvl1 - 1].y - 40 - windowSize.y;
    const std::vector<sf::Vector2f> wallsPositionLvl2 = {{200, 400}, {635, 0}, {200, 10}, {200, -120}};
    const std::vector<std::string> wallsTypesLvl2 = {"_wall", "_wall", "_wall", "_checkpoint_enabled"};
    const std::vector<int> wallsSizeLvl2 = {5, 10, 3, 1};
    segments[1].startCheckpointDir = 'l';
    segments[1].endCheckpointDir = 'r';
    initWallsNextSegment(segments[1].walls, lvl2SegmentStart, countWallsLvl1, wallsPositionLvl1, wallsTypesLvl1, wallsSizeLvl1);
}

void drawWalls(sf::RenderWindow &window, std::vector<Segment> &segments)
{
    const int segmentCount = (int)segments.size();
    for (int i = 0; i < segmentCount; i++)
    {
        int wallsCountOfSegment = (int)segments[i].walls.size();
        for (int j = 0; j < wallsCountOfSegment; j++)
        {
            segments[i].walls[j].img.setPosition(segments[i].walls[j].position);
            window.draw(segments[i].walls[j].img);
        }
    }
}

std::vector<Wall> getAllWalls(std::vector<Segment> segments)
{
    std::vector<Wall> walls;
    const int segmentCount = (int)segments.size();
    for (int i = 0; i < segmentCount; i++)
    {
        int wallsCountOfSegment = (int)segments[i].walls.size();
        for (int j = 0; j < wallsCountOfSegment; j++)
        {
            walls.push_back(segments[i].walls[j]);
        }
    }
    return walls;
}