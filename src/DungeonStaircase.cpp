#include "DungeonStaircase.h"

#include <iostream>

DungeonStaircase::DungeonStaircase(DungeonLayer& parentLayer, int x, int y, bool goesUp)
    : DungeonVisitable(goesUp ? "You find a stairway going up." : "You find a stairway going down.")
    , m_parentLayer(parentLayer)
    , m_x(x)
    , m_y(y)
    , m_goesUp(goesUp)
{
}

void DungeonStaircase::visit()
{
    m_isVisited = true;
    std::cout << "You find a staircase going " << (m_goesUp ? "up" : "down") << '\n';
}

void DungeonStaircase::print()
{
    const char* room = isVisited() ? (m_goesUp ? "H" : "L") : ".";

    bool hallwayRightVisited = false;
    if (m_x + 1 < m_parentLayer.config().width) {
        hallwayRightVisited = isVisited() && m_parentLayer.visitables()[m_x + 1][m_y]->isVisited();
    }

    const char* rightHall = hallwayRightVisited ? "--" : "  ";

    if (m_parentLayer.hero().x() == m_x && m_parentLayer.hero().y() == m_y)
        std::cout << 'P' << rightHall;
    else
        std::cout << room << rightHall;
}
