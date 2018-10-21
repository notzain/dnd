#include "Dungeon.h"
#include "DungeonStaircase.h"
#include <stdexcept>
#include <iostream>

Dungeon::Dungeon(DungeonConfiguration* configuration, Hero* hero)
    : m_config(configuration)
    , m_hero(hero)
    , m_activeLayer(0)
    , m_isCleared(false)
{
    if (m_config->layers <= 0 || m_config->layers > 10) {
        throw std::runtime_error("Invalid number of layers.");
    }
    m_layers = new DungeonLayer*[m_config->layers];

    generateLayers();
}

Dungeon::~Dungeon()
{
    for (int i = 0; i < m_config->layers; ++i) {
        delete m_layers[i];
    }
    delete[] m_layers;
    delete m_config->monsters;
    delete m_config;
    delete m_hero;
}

void Dungeon::generateLayers()
{
    const auto levelRangePerLayer = static_cast<int>(10.f / m_config->layers);

    for (int i = 0; i < m_config->layers; ++i) {
        const bool hasBoss = (i == m_config->layers - 1);
        const int stairsUp = (i != 0);
        const int stairsDown = (i != m_config->layers - 1);

        auto* layerConfig = new DungeonLayerConfiguration{
            /*.width =*/m_config->height,
            /*.height =*/m_config->width,

            /*.numStairsUp =*/stairsUp,
            /*.numStairsDown = */ stairsDown,

            /*.minEnemyLevel = */ i,
            /*.maxEnemyLevel =*/i + levelRangePerLayer,

            /*.hasBoss = */ hasBoss,
            /*.monsters =*/m_config->monsters
        };

        m_layers[i] = new DungeonLayer(layerConfig, *m_hero, *this);
    }
}

DungeonLayer** Dungeon::layers() const
{
    return m_layers;
}

DungeonLayer& Dungeon::activeLayer() const
{
    return *m_layers[m_activeLayer];
}

void Dungeon::nextLayer()
{
    m_activeLayer++;
    if (m_activeLayer == m_config->layers) {
        m_isCleared = true;
        return;
    }
    for (int i = 0; i < activeLayer().config().width; ++i) {
        for (int j = 0; j < activeLayer().config().height; ++j) {
            if (auto* room = dynamic_cast<DungeonStaircase*>(activeLayer().visitables()[i][j])) {
                if (room->goesUp()) {
                    m_hero->setX(i);
                    m_hero->setY(j);
                    return;
                }
            }
        }
    }
}

void Dungeon::prevLayer()
{
    m_activeLayer--;
    if (m_activeLayer < 0) {
        m_isCleared = true;
        return;
    }
    for (int i = 0; i < activeLayer().config().width; ++i) {
        for (int j = 0; j < activeLayer().config().height; ++j) {
            if (auto* room = dynamic_cast<DungeonStaircase*>(activeLayer().visitables()[i][j])) {
                if (!room->goesUp()) {
                    m_hero->setX(i);
                    m_hero->setY(j);
                    return;
                }
            }
        }
    }
}