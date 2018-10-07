#include "DungeonRoom.h"
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
    m_isVisited = true;
    std::cout << "You enter a room.\n" << description() << "\n\n";
}

void DungeonRoom::print()
{
    const char* room = (isVisited() ? "N" : ".");

    bool hallwayRightVisited = false;
    if (m_y + 1 < m_parentLayer.config().height) {
        hallwayRightVisited = isVisited() && m_parentLayer.visitables()[m_x][m_y + 1]->isVisited();
    }

    const char* rightHall = hallwayRightVisited ? "—" : "  ";

    if (m_parentLayer.hero().x() == m_x && m_parentLayer.hero().y() == m_y)
        std::cout << 'P' << rightHall;
    else
        std::cout << room << rightHall;
}
