#include "FightSystem.h"
#include "Hero.h"
#include "Monster.h"
#include "RNG.h"
#include "TravelSystem.h"
#include "InventorySystem.h"
#include "ExperienceSystem.h"
#include <iostream>

FightSystem& FightSystem::instance()
{
    static FightSystem system;
    return system;
}

void FightSystem::fight(Hero& hero, Monster& monster, DungeonLayer& layer)
{
    std::cout << "You face a monster!\n";
    int monsterHp = monster.hitpoints();

    while (hero.hitpoints() > 0 && monsterHp > 0) {
        std::cout << "\n\n";
        std::cout << hero.name() << " | "
                  << "hp: " << hero.hitpoints() << "\n";
        std::cout << monster.name() << " | "
                  << "hp: " << monsterHp << "\n\n";

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
            monsterHp -= heroAttack;

            for (int i = 0; i < monster.attackProbability().hitRepeats; ++i) {
                if ((RNG::generate(0, 100) < monster.attackProbability().hitPercentage - hero.defence())) {
                    int monsterAttack = RNG::generate(monster.damage().minimum, monster.damage().maximum);
                    std::cout << "You get hit for " << monsterAttack << " damage.\n";
                    hero.setHitpoints(hero.hitpoints() - monsterAttack);
                } else {
                    std::cout << monster.name() << " tries to attack but misses.\n";
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
                std::cout << "\n\n\n";
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
    if (monsterHp <= 0) {
        std::cout << "You've killed " << monster.name() << "\n";
        ExperienceSystem::instance().addExperience(hero, monster);
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
