#include <iostream>

#include "DungeonLayer.h"
#include "DungeonRoom.h"
#include "Game.h"
#include "HeroFactory.h"
#include "Monster.h"
#include "MonsterReader.h"
#include "RustySword.h"
#include "SaveSystem.h"

Hero* makeHero()
{
    std::cout << "Welcome to the Mierda Dungeon.\n";
    std::cout << "Do you want to (1) make a new hero, or (2) load a previous hero? ";
    char input = 0;
    do {
        std::cin >> input;
        std::cin.ignore(1000, '\n');
    } while (input < '1' || input > '2');

    HeroFactory factory;
    if (input == '1') {
        return factory.makeDefaultHero();
    } else {
        return factory.makeFromFile("../hero.txt");
    }
}

DungeonConfiguration* makeConfig()
{
    MonsterReader monsterReader;
    MonsterArray* monsterArray = nullptr;
    try {
        monsterArray = monsterReader.createFromFile("../monsters.txt");
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n\n";
        std::cerr << "Could not read file\n";
        return nullptr;
    }

    int width = 0;
    int height = 0;
    int layers = 0;

    std::cout << "Width: ";
    std::cin >> width;
    std::cin.ignore(1000, '\n');

    std::cout << "Height: ";
    std::cin >> height;
    std::cin.ignore(1000, '\n');

    std::cout << "Layers: ";
    std::cin >> layers;
    std::cin.ignore(1000, '\n');

    auto* config = new DungeonConfiguration{
        /* int width; */ width,
        /* int height; */ height,
        /* int layers; */ layers,
        /* MonsterArray* monsters; */ monsterArray
    };
}

int main()
{
    Hero* hero = makeHero();
    if (hero == nullptr) {
        return EXIT_FAILURE;
    }

    DungeonConfiguration* config = makeConfig();
    if (config == nullptr) {
        return EXIT_FAILURE;
    }

    Dungeon dungeon(config, hero);
    Game game(dungeon, *hero);
    game.play();

    return 0;
}