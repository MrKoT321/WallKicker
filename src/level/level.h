#pragma once

struct Level
{
    Wall startCheckpoint;
    Wall endCheckpoint;
    char startCheckpointDir;
    char endCheckpointDir;
    Wall walls[];
};

void initLevels(Level levels[])
{
    Level lvl1;
    const int LVL1_COUNT_WALLS = 2;
    const sf::Vector2f wallsPosition[LVL1_COUNT_WALLS]{{345, 0}, {635, 0}};
    const char wallsTypes[LVL1_COUNT_WALLS]{'_', '_'};
    const int wallsSize[LVL1_COUNT_WALLS]{10, 10};
    levels[0] = lvl1;
    initWalls(lvl1.walls, LVL1_COUNT_WALLS, wallsPosition, wallsTypes, wallsSize);
}