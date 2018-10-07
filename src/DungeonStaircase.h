#ifndef DND_DUNGEONSTAIRCASE_H
#define DND_DUNGEONSTAIRCASE_H

#include "DungeonLayer.h"
#include "DungeonVisitable.h"

class DungeonStaircase : public DungeonVisitable {
    DungeonLayer& m_parentLayer;
    int m_x;
    int m_y;
    bool m_goesUp;

public:
    DungeonStaircase(DungeonLayer& parentLayer, int x, int y, bool goesUp);

    void visit() override;
    void print() override;
};

#endif //DND_DUNGEONSTAIRCASE_H
