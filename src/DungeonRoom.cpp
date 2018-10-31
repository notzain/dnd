#include "DungeonRoom.h"
#include "Dungeon.h"
#include "DungeonLayer.h"
#include "FightSystem.h"
#include "InventorySystem.h"
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

/*
    Make a description. 
    The returned string should be COPIED, you cant use the original pointer!
*/
static const char* makeDescription()
{
    // create a buffer, set to 0
    static char string[512];
    memset(string, 0, 512);

    // copy random descriptions into the buffer
    strcpy(string, SizeDescriptions[RNG::generate(0, 2)]);
    strcat(string, ConditionDescriptions[RNG::generate(0, 2)]);
    strcat(string, DecorationDescriptions[RNG::generate(0, 2)]);

    return string;
}

DungeonRoom::DungeonRoom(DungeonLayer& parentLayer, int x, int y)
    : DungeonVisitable(makeDescription(), x, y)
    , m_parentLayer(parentLayer)
{
}

DungeonRoom::~DungeonRoom() = default;

void DungeonRoom::visit()
{
    std::cout << "You enter a room.\n"
              << description() << "\n\n";

    InventorySystem::instance().giveRandomItem(m_parentLayer.hero());

    if (!m_isVisited) {
        m_isVisited = true;

        int monstersToFight = RNG::generate(1, 4);
        if (monstersToFight == 1) {
            auto* monster = m_parentLayer.config().monsters->randomMonsterInRange(
                m_parentLayer.config().minEnemyLevel,
                m_parentLayer.config().maxEnemyLevel);
            FightSystem::instance().fight(m_parentLayer.hero(), *monster, m_parentLayer);
        } else {
            // if fighting multiple monsters, make a new array of monsters
            // and fill it with the monsters
            auto** monsters = new Monster*[monstersToFight];
            for (int i = 0; i < monstersToFight; ++i) {
                monsters[i] = m_parentLayer.config().monsters->randomMonsterInRange(
                    m_parentLayer.config().minEnemyLevel,
                    m_parentLayer.config().maxEnemyLevel);
            }
            FightSystem::instance().fight(m_parentLayer.hero(), monsters, monstersToFight, m_parentLayer);
            // make sure not to delete the array
            delete[] monsters;
        }
    } else {
        int chance = RNG::generate(0, 100);
        // 30% chance to fight monster on re-entering room
        if (chance < 30) {
            auto* monster = m_parentLayer.config().monsters->randomMonsterInRange(
                m_parentLayer.config().minEnemyLevel,
                m_parentLayer.config().maxEnemyLevel);
            FightSystem::instance().fight(m_parentLayer.hero(), *monster, m_parentLayer);
        }
    }
}

void DungeonRoom::printSymbol(std::ostream& str)
{
    if (m_parentLayer.hero().x() == m_x && m_parentLayer.hero().y() == m_y) {
        str << "P";
    } else {
        const char* room = (isVisited() ? "N" : ".");
        str << room;
    }
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
    if (m_x + 1 < m_parentLayer.config().width) {
        hallwayDownVisited = isVisited() && m_parentLayer.visitables()[m_x + 1][m_y]->isVisited();
    }
    const char* downHall = hallwayDownVisited ? "|  " : "   ";
    str << downHall;
}
