#include "DungeonStaircase.h"
#include "Hero.h"

#include <iostream>

DungeonStaircase::DungeonStaircase(DungeonLayer& parentLayer, int x, int y, bool goesUp)
    : DungeonVisitable(goesUp ? "You find a stairway going up." : "You find a stairway going down.", x, y)
    , m_parentLayer(parentLayer)
    , m_goesUp(goesUp)
{
}

void DungeonStaircase::visit()
{
    m_isVisited = true;
    std::cout << "You find a staircase going " << (m_goesUp ? "up" : "down") << '\n';

    char input = 0;
    while (input != 'y' && input != 'n') {
        std::cout << "Will you take the staircase? (y/n) ";
        std::cin >> input;
        std::cin.ignore(1000, '\n');

        if (input == 'y') {
            if (!m_goesUp) {
                m_parentLayer.nextLayer();
            } else {
                m_parentLayer.prevLayer();
            }
        }
    }
}

void DungeonStaircase::printSymbol(std::ostream& str)
{
    if (m_parentLayer.hero().x() == m_x && m_parentLayer.hero().y() == m_y) {
        str << "P";
    } else {
        const char* room = isVisited() ? (m_goesUp ? "H" : "L") : ".";
        str << (m_goesUp ? "H" : "L");
    }
}

void DungeonStaircase::printHorizontalNeighbour(std::ostream& str)
{
    bool hallwayRightVisited = false;
    if (m_y + 1 < m_parentLayer.config().height) {
        hallwayRightVisited = isVisited() && m_parentLayer.visitables()[m_x][m_y + 1]->isVisited();
    }
    const char* rightHall = hallwayRightVisited ? "--" : "  ";
    str << rightHall;
}

void DungeonStaircase::printVerticalNeighbour(std::ostream& str)
{
    bool hallwayDownVisited = false;
    if (m_x + 1 < m_parentLayer.config().height) {
        hallwayDownVisited = isVisited() && m_parentLayer.visitables()[m_x + 1][m_y]->isVisited();
    }
    const char* downHall = hallwayDownVisited ? "¦  " : "   ";
    str << downHall;
}
