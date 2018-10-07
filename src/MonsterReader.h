#ifndef DND_MONSTERFACTORY_H
#define DND_MONSTERFACTORY_H

#include "Monster.h"

struct MonsterArray {
    Monster** array{};
    std::size_t length{};

    virtual ~MonsterArray()
    {
        for (int i = 0; i < length; ++i) {
            delete array[i];
        }
        delete[] array;
    }
};

class MonsterReader {
    MonsterArray* m_monsters;

public:
    MonsterReader();
    MonsterArray* createFromFile(const char* filename);

private:
    Level stringToLevel(const char *level) const;
};

#endif //DND_MONSTERFACTORY_H
