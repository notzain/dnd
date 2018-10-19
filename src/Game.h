#ifndef DND_GAME_H
#define DND_GAME_H

#include "Dungeon.h"

class Game {
    Dungeon& m_dungeon;
    Hero& m_hero;
public:
    Game(Dungeon &dungeon, Hero &hero);
    void play();
};


#endif //DND_GAME_H
