#ifndef DND_DUNGEONBOSSROOM_H
#define DND_DUNGEONBOSSROOM_H

#include "DungeonLayer.h"

class DungeonBossRoom : public DungeonVisitable {
    DungeonLayer& m_parentLayer;
    bool m_isVisited = false;
    int m_x,
        m_y;

public:
    DungeonBossRoom(DungeonLayer& parentLayer, int x, int y);

    void visit() override;

    void printSymbol(std::ostream &str) override;

    void printHorizontalNeighbour(std::ostream &str) override;

    void printVerticalNeighbour(std::ostream &str) override;
};

#endif //DND_DUNGEONBOSSROOM_H
