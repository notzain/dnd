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
    MonsterArray* monsterArray = nullptr;
    try {
        monsterArray = monsterReader.createFromFile("../monsters.txt");
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n\n";
        std::cerr << "Could not read file\n";
        return EXIT_FAILURE;
    }
    auto* config = new DungeonConfiguration{
        /* int width; */ 10,
        /* int height; */ 10,
        /* int layers; */ 3,
        /* MonsterArray* monsters; */ monsterArray
    };

    Hero hero("Zain", 0, 100, 0, 30, 30);
    hero.inventory().addItem(new RustySword());

    Dungeon dungeon(config, hero);

    Game game(dungeon, hero);
    game.play();

    return 0;
}