#ifndef DND_GAME_H
#define DND_GAME_H


#include "DungeonLayer.h"

class Game {
    DungeonLayer& m_layer;
    Hero& m_hero;
public:
    Game(DungeonLayer &layer, Hero &hero);
    void play();
};


#endif //DND_GAME_H
