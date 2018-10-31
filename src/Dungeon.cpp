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
    // Check if config layers is in bound, else throw error
    if (m_config->layers <= 0 || m_config->layers > 10) {
        // Make sure to delete all pointers
        delete m_hero;
        delete m_config->monsters;
        delete m_config;
        throw std::runtime_error("Invalid number of layers.");
    }
    m_layers = new DungeonLayer*[m_config->layers];

    generateLayers();
}

Dungeon::~Dungeon()
{
    // Delete all relevant pointers
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
    // Shitty way to "calculate" the min and max level of enemies per layer
    const auto levelRangePerLayer = static_cast<int>(10.f / m_config->layers);

    for (int i = 0; i < m_config->layers; ++i) {
        // layer has a boss if its the last layer
        const bool hasBoss = (i == m_config->layers - 1);
        // if its the first layer, there is no stairs up
        const int stairsUp = (i != 0);
        // if its the last layer, there is no stairs down
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
    // if the last layer has been reached, the dungeon is cleared
    if (m_activeLayer == m_config->layers) {
        m_isCleared = true;
        return;
    }

    // hacky~
    // if the player goes a layer up, make sure the room he starts on in the next layer is the same stairway, but down
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
    // if the player exits the dungeon.. not cleared but same flag used
    if (m_activeLayer < 0) {
        m_isCleared = true;
        return;
    }

    // if the player goes down by stairs, make sure he lands on the same stairway up
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