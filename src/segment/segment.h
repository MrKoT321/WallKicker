#pragma once

struct Segment
{
    char startCheckpointDir;
    char endCheckpointDir;
    std::vector<Wall> walls;
    bool isActive = false;
    bool isCheckpointPassed = false;
};

void initSegments(std::vector<Segment> &segments, sf::Vector2u windowSize)
{
    segments.clear();
    segments.push_back(Segment());
    segments.push_back(Segment());
    const int countWallsLvl1 = 4;
    for (int i = 0; i < countWallsLvl1; i++)
        segments[0].walls.push_back(Wall());
    const std::vector<sf::Vector2f> wallsPositionLvl1 = {{345, 400}, {635, 0}, {200, 10}, {200, -170}};
    const std::vector<std::string> wallsTypesLvl1 = {"_wall", "_wall", "_wall", "_checkpoint_enabled"};
    const std::vector<int> wallsSizeLvl1 = {5, 10, 3, 1};
    const std::vector<char> wallsFeatureLvl1 = {'s', 's', 's', 'c'};
    segments[0].startCheckpointDir = 'l';
    segments[0].endCheckpointDir = 'r';
    segments[0].isActive = true;
    initWallsSegment(segments[0].walls, countWallsLvl1, wallsPositionLvl1, wallsTypesLvl1, wallsSizeLvl1, wallsFeatureLvl1);

    const int countWallsLvl2 = 4;
    for (int i = 0; i < countWallsLvl2; i++)
        segments[1].walls.push_back(Wall());
    const float lvl2SegmentStart = wallsPositionLvl1[countWallsLvl1 - 1].y - 120 - windowSize.y;
    const std::vector<sf::Vector2f> wallsPositionLvl2 = {{200, 400}, {635, 0}, {200, 10}, {200, -170}};
    const std::vector<std::string> wallsTypesLvl2 = {"_wall", "_wall", "_wall", "_checkpoint_enabled"};
    const std::vector<int> wallsSizeLvl2 = {5, 10, 3, 1};
    const std::vector<char> wallsFeatureLvl2 = {'s', 's', 's', 'c'};
    segments[1].startCheckpointDir = 'l';
    segments[1].endCheckpointDir = 'r';
    initWallsSegment(segments[1].walls, countWallsLvl2, wallsPositionLvl2, wallsTypesLvl2, wallsSizeLvl2, wallsFeatureLvl2, lvl2SegmentStart);
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

void initNextSegment(std::vector<Segment> &segments, sf::Vector2u windowSize)
{
    int activeSegmentIndex = 0;
    if (segments[1].isActive)
        activeSegmentIndex = 1;

    segments[activeSegmentIndex].isActive = false;
    segments[1 - activeSegmentIndex].isActive = true;

    const int countWalls = 4;
    segments[activeSegmentIndex].walls.clear();
    for (int i = 0; i < countWalls; i++)
        segments[activeSegmentIndex].walls.push_back(Wall());
    const int prevSegmentLastWallIndex = (int)segments[1 - activeSegmentIndex].walls.size() - 1;
    const float segmentStart = segments[1 - activeSegmentIndex].walls[prevSegmentLastWallIndex].position.y - 120 - windowSize.y;
    const std::vector<sf::Vector2f> wallsPosition = {{200, 400}, {635, 0}, {200, 10}, {200, -170}};
    const std::vector<std::string> wallsTypes = {"_wall", "_wall", "_wall", "_checkpoint_enabled"};
    const std::vector<int> wallsSize = {5, 10, 3, 1};
    const std::vector<char> wallsFeature = {'s', 's', 's', 'c'};
    segments[activeSegmentIndex].startCheckpointDir = 'l';
    segments[activeSegmentIndex].endCheckpointDir = 'r';
    segments[activeSegmentIndex].isCheckpointPassed = false;
    initWallsSegment(segments[activeSegmentIndex].walls, countWalls, wallsPosition, wallsTypes, wallsSize, wallsFeature, segmentStart);
}

sf::Vector2f getCheckpointFromActiveSegment(std::vector<Segment> segments)
{
    int activeSegmentIndex = 0;
    if (segments[1].isActive)
        activeSegmentIndex = 1;
    const int activeSegmentWallsCount = (int)segments[activeSegmentIndex].walls.size();
    return segments[activeSegmentIndex].walls[activeSegmentWallsCount - 1].position;
}

bool isPrevSegmentEnded(std::vector<Segment> segments, sf::Vector2u windowSize)
{
    const sf::Vector2f prevCheckpointPosition = getCheckpointFromActiveSegment(segments);
    return windowSize.y + 20 < prevCheckpointPosition.y;
}

bool isCurrSegmentCompleted(std::vector<Segment> segments, float heroPositionY)
{
    int activeSegmentIndex = 0;
    if (segments[1].isActive)
        activeSegmentIndex = 1;
    if (segments[activeSegmentIndex].isCheckpointPassed)
        return false;
    const int activeSegmentWallsCount = (int)segments[activeSegmentIndex].walls.size();
    float lastCurrWallPositionY = segments[activeSegmentIndex].walls[activeSegmentWallsCount - 1].position.y;
    return heroPositionY < lastCurrWallPositionY;
}

void updateSegmentPositionWithScreenMove(std::vector<Segment> &segments, int screenChangeSpeed, float dt)
{
    const int segmentCount = (int)segments.size();
    for (int i = 0; i < segmentCount; i++)
    {
        int wallsCountOfSegment = (int)segments[i].walls.size();
        for (int j = 0; j < wallsCountOfSegment; j++)
        {
            segments[i].walls[j].position.y += screenChangeSpeed * dt;
        }
    }
}

void updateSegmentWithLvlComplete(std::vector<Segment> &segments)
{
    int activeSegmentIndex = 0;
    if (segments[1].isActive)
        activeSegmentIndex = 1;
    const int activeSegmentWallsCount = (int)segments[activeSegmentIndex].walls.size();
    updateCheckpointImgWithLvlComplete(segments[activeSegmentIndex].walls[activeSegmentWallsCount - 1]);
    segments[activeSegmentIndex].isCheckpointPassed = true;
}