#include "DungeonBossRoom.h"
#include "Dungeon.h"
#include "FightSystem.h"
#include "Hero.h"

#include <iostream>

DungeonBossRoom::DungeonBossRoom(DungeonLayer& parentLayer, int x, int y)
    : DungeonVisitable("You confront a terrifying monster!", x, y)
    , m_parentLayer(parentLayer)
    , m_isVisited(false)
{
}

void DungeonBossRoom::visit()
{
    std::cout << "You enter a room.\n"
              << description() << "\n\n";
    std::cout << "There is no escape.\n";

    auto* boss = m_parentLayer.config().monsters->randomMonsterWithLevel(static_cast<int>(Level::BOSS));
    FightSystem::instance().fightBoss(m_parentLayer.hero(), *boss, m_parentLayer);
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
