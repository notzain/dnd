#ifndef DND_DUNGEONROOM_H
#define DND_DUNGEONROOM_H

#include "DungeonLayer.h"
#include "DungeonVisitable.h"

class DungeonRoom : public DungeonVisitable {
    DungeonLayer& m_parentLayer;

public:
    explicit DungeonRoom(DungeonLayer& parentLayer, int x, int y);
    ~DungeonRoom() override;

    void visit() override;


    void printSymbol(std::ostream &str) override;
    void printHorizontalNeighbour(std::ostream &str) override;
    void printVerticalNeighbour(std::ostream &str) override;

};

#endif //DND_DUNGEONROOM_H
