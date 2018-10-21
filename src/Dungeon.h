#ifndef DND_DUNGEON_H
#define DND_DUNGEON_H

#include "Monster.h"
#include "DungeonLayer.h"
#include "Hero.h"

struct DungeonConfiguration {
    int width;
    int height;
    int layers;
    MonsterArray* monsters;
};

class Dungeon {
    DungeonConfiguration* m_config;
    DungeonLayer** m_layers;
    Hero* m_hero;
    int m_activeLayer;
    bool m_isCleared;

public:
    Dungeon(DungeonConfiguration* configuration, Hero* hero);
    virtual ~Dungeon();

    void nextLayer();
    void prevLayer();
    DungeonLayer** layers() const;
    DungeonLayer& activeLayer() const;
    bool isCleared() const
    {
        return m_isCleared;
    }

private:
    void generateLayers();
};

#endif //DND_DUNGEON_H
