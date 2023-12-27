#pragma once

struct Segment
{
    std::vector<Wall> walls;
    bool isActive = false;
    bool isCheckpointPassed = false;
};

int random(int low, int high)
{
    return low + rand() % (high - low + 1);
}

int getNextLvlVariantNum()
{
    const int maxNextLvlVariants = 4;
    return random(1, maxNextLvlVariants);
}

void createSegmentVariant1(Segment &segment, sf::Vector2u windowSize, float segmentStart)
{
    const int countWalls = 9;
    for (int i = 0; i < countWalls; i++)
        segment.walls.push_back(Wall());
    const std::vector<sf::Vector2f> wallsPosition = {{200, 160}, {442, 355}, {442, 470}, {442, 585}, {722, 160}, {722, -516}, {462, -319}, {442, -161}, {200, -516}};
    const std::vector<std::string> wallsTypes = {getSimpleWallType(), getBothSpikeWallType(), getBothSpikeWallType(), getBothSpikeWallType(), getSimpleWallType(), getSimpleWallType(), getRightSpikeWallType(), getBothSpikeWallType(), getEnableCheckpointWallType()};
    const std::vector<int> wallsSize = {7, 1, 1, 1, 7, 7, 1, 1, 1};
    const std::vector<char> wallsFeature = {getSimpleWallFeature(), getBothSpikeWallFeature(), getBothSpikeWallFeature(), getBothSpikeWallFeature(), getSimpleWallFeature(), getSimpleWallFeature(), getRightSpikeWallFeature(), getBothSpikeWallFeature(), getCheckpointWallFeature()};
    createWallsSegment(segment.walls, countWalls, wallsPosition, wallsTypes, wallsSize, wallsFeature, segmentStart);
}

void createSegmentVariant2(Segment &segment, sf::Vector2u windowSize, float segmentStart)
{
    const int countWalls = 8;
    for (int i = 0; i < countWalls; i++)
        segment.walls.push_back(Wall());
    const std::vector<sf::Vector2f> wallsPosition = {{80, 446}, {313, 442}, {546, 442}, {780, 89}, {780, -97}, {481, -97}, {200, -310}, {200, -516}};
    const std::vector<std::string> wallsTypes = {getSimpleWallType(), getRightSpikeWallType(), getRightSpikeWallType(), getSimpleWallType(), getBounceWallType(), getRightSpikeWallType(), getSimpleWallType(), getEnableCheckpointWallType()};
    const std::vector<int> wallsSize = {3, 1, 1, 8, 1, 1, 4, 1};
    const std::vector<char> wallsFeature = {getSimpleWallFeature(), getRightSpikeWallFeature(), getRightSpikeWallFeature(), getSimpleWallFeature(), getBounceWallFeature(), getRightSpikeWallFeature(), getSimpleWallFeature(), getCheckpointWallFeature()};
    createWallsSegment(segment.walls, countWalls, wallsPosition, wallsTypes, wallsSize, wallsFeature, segmentStart);
}

void createSegmentVariant3(Segment &segment, sf::Vector2u windowSize, float segmentStart)
{
    const int countWalls = 6;
    for (int i = 0; i < countWalls; i++)
        segment.walls.push_back(Wall());
    const std::vector<sf::Vector2f> wallsPosition = {{200, 505}, {450, 390}, {700, -69}, {500, -189}, {328, -349}, {200, -516}};
    const std::vector<std::string> wallsTypes = {getSimpleWallType(), getSimpleWallType(), getSimpleWallType(), getSimpleWallType(), getSimpleWallType(), getEnableCheckpointWallType()};
    const std::vector<int> wallsSize = {2, 2, 7, 2, 2, 1};
    const std::vector<char> wallsFeature = {getSimpleWallFeature(), getSimpleWallFeature(), getSimpleWallFeature(), getSimpleWallFeature(), getSimpleWallFeature(), getCheckpointWallFeature()};
    createWallsSegment(segment.walls, countWalls, wallsPosition, wallsTypes, wallsSize, wallsFeature, segmentStart);
}

void createSegmentVariant4(Segment &segment, sf::Vector2u windowSize, float segmentStart)
{
    const int countWalls = 9;
    for (int i = 0; i < countWalls; i++)
        segment.walls.push_back(Wall());
    const std::vector<sf::Vector2f> wallsPosition = {{200, 555}, {200, 385}, {200, 215}, {200, 45}, {200, -125}, {200, -295}, {200, -465}, {200, -635}, {200, -805}};
    const std::vector<std::string> wallsTypes = {getBounceWallType(), getSimpleWallType(), getBounceWallType(), getSimpleWallType(), getBounceWallType(), getSimpleWallType(), getBounceWallType(), getSimpleWallType(), getEnableCheckpointWallType()};
    const std::vector<int> wallsSize = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    const std::vector<char> wallsFeature = {getBounceWallFeature(), getSimpleWallFeature(), getBounceWallFeature(), getSimpleWallFeature(), getBounceWallFeature(), getSimpleWallFeature(), getBounceWallFeature(), getSimpleWallFeature(), getCheckpointWallFeature()};
    createWallsSegment(segment.walls, countWalls, wallsPosition, wallsTypes, wallsSize, wallsFeature, segmentStart);
}

void chooseSegmentToCreate(Segment &segment, sf::Vector2u windowSize, float segmentStart)
{
    const int nextLvlVariantNum = getNextLvlVariantNum();
    segment.isCheckpointPassed = false;
    segment.walls.clear();

    if (nextLvlVariantNum == 1)
        createSegmentVariant1(segment, windowSize, segmentStart);
    if (nextLvlVariantNum == 2)
        createSegmentVariant2(segment, windowSize, segmentStart);
    if (nextLvlVariantNum == 3)
        createSegmentVariant3(segment, windowSize, segmentStart);
    if (nextLvlVariantNum == 4)
        createSegmentVariant4(segment, windowSize, segmentStart);
}

void initSegments(std::vector<Segment> &segments, sf::Vector2u windowSize)
{
    segments.clear();
    segments.push_back(Segment());
    segments.push_back(Segment());
    const int countWallsLvl1 = 4;
    for (int i = 0; i < countWallsLvl1; i++)
        segments[0].walls.push_back(Wall());
    const std::vector<sf::Vector2f> wallsPositionLvl1 = {{345, 400}, {635, 0}, {200, 10}, {200, -170}};
    const std::vector<std::string> wallsTypesLvl1 = {getSimpleWallType(), getSimpleWallType(), getSimpleWallType(), getEnableCheckpointWallType()};
    const std::vector<int> wallsSizeLvl1 = {5, 10, 3, 1};
    const std::vector<char> wallsFeatureLvl1 = {getSimpleWallFeature(), getSimpleWallFeature(), getSimpleWallFeature(), getCheckpointWallFeature()};
    segments[0].isActive = true;
    createWallsSegment(segments[0].walls, countWallsLvl1, wallsPositionLvl1, wallsTypesLvl1, wallsSizeLvl1, wallsFeatureLvl1);

    const int deltaSegmentsPositions = 60;
    const float lvl2SegmentStart = wallsPositionLvl1[countWallsLvl1 - 1].y - deltaSegmentsPositions - windowSize.y;
    chooseSegmentToCreate(segments[1], windowSize, lvl2SegmentStart);
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

int getActiveSegmentIndex(std::vector<Segment> &segments)
{
    return segments[1].isActive ? 1 : 0;
}

void createNextSegment(std::vector<Segment> &segments, sf::Vector2u windowSize)
{
    int activeSegmentIndex = getActiveSegmentIndex(segments);

    segments[activeSegmentIndex].isActive = false;
    segments[1 - activeSegmentIndex].isActive = true;

    const int prevSegmentLastWallIndex = (int)segments[1 - activeSegmentIndex].walls.size() - 1;
    const int deltaSegmentsPositions = 60;
    const float segmentStart = segments[1 - activeSegmentIndex].walls[prevSegmentLastWallIndex].position.y - deltaSegmentsPositions - windowSize.y;
    chooseSegmentToCreate(segments[activeSegmentIndex], windowSize, segmentStart);
}

sf::Vector2f getCheckpointPositionFromActiveSegment(std::vector<Segment> &segments)
{
    int activeSegmentIndex = getActiveSegmentIndex(segments);
    const int activeSegmentWallsCount = (int)segments[activeSegmentIndex].walls.size();
    return segments[activeSegmentIndex].walls[activeSegmentWallsCount - 1].position;
}

bool isPrevSegmentEnded(std::vector<Segment> &segments, sf::Vector2u windowSize)
{
    const int deltaSegmentAfterEnded = 20;
    const sf::Vector2f prevCheckpointPosition = getCheckpointPositionFromActiveSegment(segments);
    return windowSize.y + deltaSegmentAfterEnded < prevCheckpointPosition.y;
}

bool isCurrSegmentCompleted(std::vector<Segment> &segments, float heroPositionY)
{
    int activeSegmentIndex = getActiveSegmentIndex(segments);
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
    int activeSegmentIndex = getActiveSegmentIndex(segments);
    const int activeSegmentWallsCount = (int)segments[activeSegmentIndex].walls.size();
    updateCheckpointImgWithLvlComplete(segments[activeSegmentIndex].walls[activeSegmentWallsCount - 1]);
    segments[activeSegmentIndex].isCheckpointPassed = true;
}