#ifndef DND_DUNGEON_H
#define DND_DUNGEON_H

#include "DungeonLayer.h"

struct DungeonConfiguration {
    int width;
    int height;
    int layers;
};

class Dungeon {
    DungeonConfiguration m_config;
    DungeonLayer* m_layers;
};

#endif //DND_DUNGEON_H
