#include "FightSystem.h"
#include "Hero.h"
#include "Monster.h"
#include "RNG.h"
#include "TravelSystem.h"
#include "InventorySystem.h"
#include <iostream>

FightSystem& FightSystem::instance()
{
    static FightSystem system;
    return system;
}

void FightSystem::fight(Hero& hero, Monster& monster, DungeonLayer& layer)
{
    std::cout << "You face a monster!\n";

    while (hero.hitpoints() > 0 && monster.hitpoints() > 0) {
        std::cout << "\n\n";
        std::cout << hero.name() << " | "
                  << "hp: " << hero.hitpoints() << "\n";
        std::cout << monster.name() << " | "
                  << "hp: " << monster.hitpoints() << "\n\n";

        char choice = '0';
        while (choice <= '0' || choice >= '4') {
            std::cout << "1. Fight, 2. Run, 3. Use item\n\n";
            std::cin >> choice;
            std::cin.ignore(10000, '\n');
        }

        switch (choice) {
        case '1': {
            int heroAttack = hero.attack();
            std::cout << "You hit the monster for " << heroAttack << "dmg\n";
            monster.setHitpoints(monster.hitpoints() - heroAttack);

            for (int i = 0; i < monster.attackProbability().hitRepeats; ++i) {
                if ((RNG::generate(0, 100) < monster.attackProbability().hitPercentage)) {
                    int monsterAttack = RNG::generate(monster.damage().minimum, monster.damage().maximum);
                    std::cout << "You get hit for " << monsterAttack << " damage.\n";
                    hero.setHitpoints(hero.hitpoints() - monsterAttack);
                }
            }
        } break;
        case '2': {
            std::cout << "You run away in direction: (w,a,s,d): ";
            char input;
            std::cin >> input;
            std::cin.ignore(10000, '\n');

            // 50% chance to run
            if (RNG::generate(0, 1) == 0) {
                TravelSystem::instance().travel(input, hero, layer);
                return;
            }
            std::cout << "You failed to run away.\n\n";
        } break;
        case '3': {
            InventorySystem::instance().use(hero, monster);
        } break;
        default:
            break;
        }
    }
}

void FightSystem::fight(Hero& hero, Monster** monsters, std::size_t numMonsters, DungeonLayer& layer)
{
    auto monstersAlive = [&]() -> bool {
        for (int i = 0; i < numMonsters; ++i) {
            if (monsters[i]->hitpoints() > 0) {
                return false;
            }
        }
        return true;
    };

    while (hero.hitpoints() > 0 && monstersAlive()) {
    }
}
