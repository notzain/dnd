#ifndef DND_DUNGEONLAYER_H
#define DND_DUNGEONLAYER_H

#include "DungeonVisitable.h"
class Dungeon;
class Hero;
class MonsterArray;

struct DungeonLayerConfiguration {
    int width{},
        height{};

    int numStairsUp{};
    int numStairsDown{};

    int minEnemyLevel{};
    int maxEnemyLevel{};

    bool hasBoss{};

    MonsterArray* monsters{};
};

class DungeonLayer {
    Dungeon& m_parentDungeon;
    DungeonLayerConfiguration* m_config;
    DungeonVisitable*** m_visitables;

    Hero& m_hero;

public:
    explicit DungeonLayer(DungeonLayerConfiguration* configuration, Hero& hero, Dungeon& parent);
    virtual ~DungeonLayer();

    DungeonVisitable*** visitables() const;
    const DungeonLayerConfiguration& config() const;
    Hero& hero() const;

    void nextLayer();
    void prevLayer();

    void visit(int x, int y);
    void print() const;

private:
    void generateLayer();
};

#endif //DND_DUNGEONLAYER_H
