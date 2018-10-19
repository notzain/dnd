#include "DungeonBossRoom.h"
#include "Hero.h"

#include <iostream>

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

void DungeonBossRoom::printSymbol(std::ostream& str)
{
    if (m_parentLayer.hero().x() == m_x && m_parentLayer.hero().y() == m_y) {
        str << "P";
    } else {
        const char* room = (isVisited() ? "B" : ".");
        str << "B";
    }
}

void DungeonBossRoom::printHorizontalNeighbour(std::ostream& str)
{
    bool hallwayRightVisited = false;
    if (m_y + 1 < m_parentLayer.config().height) {
        hallwayRightVisited = isVisited() && m_parentLayer.visitables()[m_x][m_y + 1]->isVisited();
    }
    const char* rightHall = hallwayRightVisited ? "--" : "  ";
    str << rightHall;
}

void DungeonBossRoom::printVerticalNeighbour(std::ostream& str)
{
    bool hallwayDownVisited = false;
    if (m_x + 1 < m_parentLayer.config().height) {
        hallwayDownVisited = isVisited() && m_parentLayer.visitables()[m_x + 1][m_y]->isVisited();
    }
    const char* downHall = hallwayDownVisited ? "¦  " : "   ";
    str << downHall;
}
