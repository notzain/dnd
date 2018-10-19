#include "DungeonRoom.h"
#include "FightSystem.h"
#include "RNG.h"
#include <iostream>

const char* SizeDescriptions[] = {
    "You can barely move around in this tiny room.",
    "This room would make a nice bedroom.",
    "The room is pretty big.",
};

const char* ConditionDescriptions[] = {
    " It looks like it has been recently used.",
    " You see mice running around.",
    " There are webcobs hanging on the ceiling.",
};

const char* DecorationDescriptions[] = {
    " There is a bed in the room.",
    " You see a table and 4 chairs.",
    " The room is empty.",
};

static const char* makeDescription()
{
    static char string[512];
    memset(string, 0, 512);

    strcpy(string, SizeDescriptions[RNG::generate(0, 2)]);
    strcat(string, ConditionDescriptions[RNG::generate(0, 2)]);
    strcat(string, DecorationDescriptions[RNG::generate(0, 2)]);

    return string;
}

DungeonRoom::DungeonRoom(DungeonLayer& parentLayer, int x, int y)
    : DungeonVisitable(makeDescription())
    , m_parentLayer(parentLayer)
    , m_x(x)
    , m_y(y)
{
}

DungeonRoom::~DungeonRoom() = default;

void DungeonRoom::visit()
{
    std::cout << "You enter a room.\n"
              << description() << "\n\n";

    if (!m_isVisited) {
        m_isVisited = true;
        auto* monster = m_parentLayer.config().monsters->array[RNG::generate(0,
            static_cast<int>(m_parentLayer.config().monsters->length - 1))];
        FightSystem::instance().fight(m_parentLayer.hero(), *monster, m_parentLayer);
    } else {
        int chance = RNG::generate(0, 100);
        // 30% chance to fight monster on re-entering room
        if (chance < 30) {
            auto* monster = m_parentLayer.config().monsters->array[RNG::generate(0,
                static_cast<int>(m_parentLayer.config().monsters->length - 1))];
            FightSystem::instance().fight(m_parentLayer.hero(), *monster, m_parentLayer);
        }
    }
}

void DungeonRoom::printSymbol(std::ostream& str)
{
    const char* room = (isVisited() ? "N" : ".");
    str << room;
}

void DungeonRoom::printHorizontalNeighbour(std::ostream& str)
{
    bool hallwayRightVisited = false;
    if (m_y + 1 < m_parentLayer.config().height) {
        hallwayRightVisited = isVisited() && m_parentLayer.visitables()[m_x][m_y + 1]->isVisited();
    }
    const char* rightHall = hallwayRightVisited ? "--" : "  ";
    str << rightHall;
}

void DungeonRoom::printVerticalNeighbour(std::ostream& str)
{
    bool hallwayDownVisited = false;
    if (m_x + 1 < m_parentLayer.config().height) {
        hallwayDownVisited = isVisited() && m_parentLayer.visitables()[m_x + 1][m_y]->isVisited();
    }
    const char* downHall = hallwayDownVisited ? "¦  " : "   ";
    str << downHall;
}
