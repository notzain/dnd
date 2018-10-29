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
        auto* hero = factory.makeFromFile("../hero.txt");
        if (hero == nullptr) {
            std::cout << "Do you want to make a new hero instead? (y/n) ";
            char newHero = 0;
            do {
                std::cin >> newHero;
                std::cin.ignore(1000, '\n');
            } while (!(newHero == 'y' || newHero == 'n'));

            if (newHero == 'y') {
                return factory.makeDefaultHero();
            } else {
                return nullptr;
            }
        } else {
            return hero;
        }
    }
}

DungeonConfiguration* makeConfig()
{
    MonsterReader monsterReader;
    MonsterArray* monsterArray = nullptr;
    try {
        monsterArray = monsterReader.createFromFile("../monsters.txt");
    } catch (const std::exception& e) {
        std::cerr << "Could not create monsters.\n";
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
    return config;
}

int main()
{
    Hero* hero = makeHero();
    if (hero == nullptr) {
        return EXIT_FAILURE;
    }

    DungeonConfiguration* config = makeConfig();
    if (config == nullptr) {
        delete hero;
        return EXIT_FAILURE;
    }

    try {
        Dungeon dungeon(config, hero);
        Game game(dungeon, *hero);
        game.play();
    } catch (const std::exception& e) {
        std::cerr << "You did something stupid.\n";
        return EXIT_FAILURE;
    }

    return 0;
}