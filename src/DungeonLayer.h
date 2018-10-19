#ifndef DND_DUNGEONLAYER_H
#define DND_DUNGEONLAYER_H

#include "DungeonVisitable.h"
#include "Hero.h"
#include "Monster.h"

struct DungeonLayerConfiguration {
    int width{},
        height{};

    int numStairsUp{};
    int numStairsDown{};

    int minEnemyLevel{};
    int maxEnemyLevel{};

    bool hasBoss{};

    MonsterArray* monsters{};
    ~DungeonLayerConfiguration() {
        delete monsters;
    }
};

class DungeonLayer {
    DungeonLayerConfiguration* m_config;
    DungeonVisitable*** m_visitables;

    Hero& m_hero;

public:
    explicit DungeonLayer(DungeonLayerConfiguration* configuration, Hero& hero);
    virtual ~DungeonLayer();

    DungeonVisitable*** visitables() const;
    const DungeonLayerConfiguration& config() const;
    Hero& hero() const;

    void visit(int x, int y);
    void print() const;

private:
    void generateLayer();
};

#endif //DND_DUNGEONLAYER_H
