#include "DungeonLayer.h"
#include "DungeonBossRoom.h"
#include "DungeonRoom.h"
#include "DungeonStaircase.h"
#include "RNG.h"

#include <iostream>
#include <sstream>

DungeonLayer::DungeonLayer(DungeonLayerConfiguration* configuration, Hero& hero)
    : m_config(configuration)
    , m_hero(hero)
{
    m_visitables = new DungeonVisitable**[m_config->width];
    for (int i = 0; i < m_config->width; ++i) {
        m_visitables[i] = new DungeonVisitable*[m_config->height];

        for (int j = 0; j < m_config->height; ++j) {
            m_visitables[i][j] = new DungeonRoom(*this, i, j);
        }
    }
    generateLayer();

    int x;
    int y;
    do {
        x = RNG::generate(0, m_config->width - 1);
        y = RNG::generate(0, m_config->height - 1);

        m_hero.setX(x);
        m_hero.setY(y);
    } while (dynamic_cast<DungeonRoom*>(m_visitables[x][y]) != nullptr);
}

DungeonLayer::~DungeonLayer()
{
    for (int i = 0; i < m_config->width; ++i) {
        for (int j = 0; j < m_config->height; ++j) {
            delete m_visitables[i][j];
        }
        delete[] m_visitables[i];
    }
    delete[] m_visitables;
    delete m_config;
}

DungeonVisitable*** DungeonLayer::visitables() const
{
    return m_visitables;
}

const DungeonLayerConfiguration& DungeonLayer::config() const
{
    return *m_config;
}

void DungeonLayer::generateLayer()
{
    int stairsUpToInit = m_config->numStairsUp;
    int stairsDownToInit = m_config->numStairsDown;
    bool bossToInit = m_config->hasBoss;

    while (stairsDownToInit--) {
        int x;
        int y;
        do {
            x = RNG::generate(0, m_config->width - 1);
            y = RNG::generate(0, m_config->height - 1);
        } while (dynamic_cast<DungeonRoom*>(m_visitables[x][y]) == nullptr);

        delete m_visitables[x][y];
        m_visitables[x][y] = new DungeonStaircase(*this, x, y, false);
    }

    while (stairsUpToInit--) {
        int x;
        int y;
        do {
            x = RNG::generate(0, m_config->width - 1);
            y = RNG::generate(0, m_config->height - 1);
        } while (dynamic_cast<DungeonRoom*>(m_visitables[x][y]) == nullptr);

        delete m_visitables[x][y];
        m_visitables[x][y] = new DungeonStaircase(*this, x, y, true);
    }

    if (bossToInit) {
        int x;
        int y;
        do {
            x = RNG::generate(0, m_config->width - 1);
            y = RNG::generate(0, m_config->height - 1);
        } while (dynamic_cast<DungeonRoom*>(m_visitables[x][y]) == nullptr);

        delete m_visitables[x][y];
        m_visitables[x][y] = new DungeonBossRoom(*this, x, y);
    }
}

void DungeonLayer::print() const
{
    std::stringstream str;
    for (int i = 0; i < m_config->width; ++i) {
        for (int j = 0; j < m_config->height; ++j) {
            m_visitables[i][j]->printSymbol(str);
            m_visitables[i][j]->printHorizontalNeighbour(str);
        }
        str << "\n";
        for (int j = 0; j < m_config->height; ++j) {
            m_visitables[i][j]->printVerticalNeighbour(str);
        }
        str << "\n";
    }
    std::cout << str.str();
}

Hero& DungeonLayer::hero() const
{
    return m_hero;
}

void DungeonLayer::visit(int x, int y)
{
    m_visitables[x][y]->visit();
}
