#include "TravelSystem.h"
#include "DungeonLayer.h"
#include "Hero.h"
#include "RNG.h"
#include <iostream>

TravelSystem& TravelSystem::instance()
{
    static TravelSystem travelSystem;
    return travelSystem;
}

bool TravelSystem::travel(char direction, Hero& hero, DungeonLayer& layer)
{
    switch (direction) {
    case 'd': {
        if (hero.y() + 1 > layer.config().height - 1) {
            std::cout << "You have hit a wall.\n";
        } else {
            hero.setY(hero.y() + 1);
        }
    } break;
    case 'w': {
        if (hero.x() - 1 < 0) {
            std::cout << "You have hit a wall.\n";
        } else {
            hero.setX(hero.x() - 1);
        }
    } break;
    case 'a': {
        if (hero.y() - 1 < 0) {
            std::cout << "You have hit a wall.\n";
        } else {
            hero.setY(hero.y() - 1);
        }

    } break;
    case 's': {
        if (hero.x() + 1 > layer.config().width - 1) {
            std::cout << "You have hit a wall.\n";
        } else {
            hero.setX(hero.x() + 1);
        }
    } break;
    default:
        std::cout << "Invalid direction\n";
        return false;
    }
    layer.visit(hero.x(), hero.y());
    system("cls");
    return true;
}

void TravelSystem::shuffle(DungeonLayer& layer)
{
    const int tile = 0; //RNG::generate(0, layer.config().width - 1);
    auto*** rooms = layer.visitables();
    auto** prevRooms = new DungeonVisitable*[layer.config().width];
    for (int i = 0; i < layer.config().width; i++) {
        prevRooms[i] = rooms[tile][i];
    }
    for (int i = 0; i < layer.config().width; i++) {
        int newPos = std::abs(i - 1) % layer.config().width;
        prevRooms[newPos]->setX((i + 1) % layer.config().width);
        rooms[tile][i] = prevRooms[newPos];
    }
}
