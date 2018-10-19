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

    bool goesUp() const
    {
        return m_goesUp;
    }

    void visit() override;

    void printSymbol(std::ostream& str) override;
    void printHorizontalNeighbour(std::ostream& str) override;
    void printVerticalNeighbour(std::ostream& str) override;
};

#endif //DND_DUNGEONSTAIRCASE_H
