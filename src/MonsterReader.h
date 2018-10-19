#ifndef DND_MONSTERFACTORY_H
#define DND_MONSTERFACTORY_H

#include "Monster.h"

class MonsterReader {
    MonsterArray* m_monsters;

public:
    MonsterReader();
    MonsterArray* createFromFile(const char* filename);

private:
    Level stringToLevel(const char *level) const;
};

#endif //DND_MONSTERFACTORY_H
