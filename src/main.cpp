#include <iostream>

#include "DungeonLayer.h"
#include "DungeonRoom.h"
#include "Monster.h"
#include "MonsterReader.h"
#include "Game.h"

int main()
{
    DungeonLayerConfiguration configuration{
        .width = 10,
        .height = 5,

        .numStairsUp = 1,
        .numStairsDown = 1,

        .minEnemyLevel = 1,
        .maxEnemyLevel = 3,

        .hasBoss = false
    };
    Hero hero("Zain", 0, 100, 0, 30, 30);
    DungeonLayer layer(configuration, hero);

    Game game(layer, hero);
    game.play();

    return 0;
}