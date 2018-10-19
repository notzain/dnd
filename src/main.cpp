#include <iostream>

#include "DungeonLayer.h"
#include "DungeonRoom.h"
#include "Game.h"
#include "Monster.h"
#include "MonsterReader.h"
#include "RustySword.h"

int main()
{
    MonsterReader monsterReader;
    auto* config = new DungeonLayerConfiguration{
        .width = 10,
        .height = 5,

        .numStairsUp = 1,
        .numStairsDown = 1,

        .minEnemyLevel = 1,
        .maxEnemyLevel = 3,

        .hasBoss = false,
        .monsters = monsterReader.createFromFile(("../monsters.txt"))
    };

    Hero hero("Zain", 0, 100, 0, 30, 30);
    hero.inventory().addItem(new RustySword());
    DungeonLayer layer(config, hero);

    Game game(layer, hero);
    game.play();

    return 0;
}