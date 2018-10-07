#include "DungeonBossRoom.h"

DungeonBossRoom::DungeonBossRoom(DungeonLayer& parentLayer, int x, int y)
    : DungeonVisitable("You confront a terrifying monster!")
    , m_parentLayer(parentLayer)
    , m_isVisited(false)
    , m_x(x)
    , m_y(y)
{
}

void DungeonBossRoom::visit()
{
}

void DungeonBossRoom::print()
{
}
