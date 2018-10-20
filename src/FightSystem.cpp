#include "FightSystem.h"
#include "DungeonLayer.h"
#include "ExperienceSystem.h"
#include "Hero.h"
#include "InventorySystem.h"
#include "Monster.h"
#include "RNG.h"
#include "TravelSystem.h"
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

            if (monsterHp <= 0) {
                std::cout << "You've killed " << monster.name() << "\n";
                ExperienceSystem::instance().addExperience(hero, monster);
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
}

void FightSystem::fight(Hero& hero, Monster** monsters, std::size_t numMonsters, DungeonLayer& layer)
{
    std::cout << "You encounter multiple enemies!\n";
    int* monsterHp = new int[numMonsters]{ 0 };
    for (int i = 0; i < numMonsters; ++i) {
        monsterHp[i] = monsters[i]->hitpoints();
    }
    const auto monstersAlive = [&]() -> bool {
        for (int i = 0; i < numMonsters; ++i) {
            if (monsterHp[i] > 0) {
                return true;
            }
        }
        return false;
    };

    while (hero.hitpoints() > 0 && monstersAlive()) {
        for (int i = 0; i < numMonsters; ++i) {
            if (monsterHp[i] > 0) {
                std::cout << "(" << i << ")"
                          << " " << monsters[i]->name() << " | "
                          << monsterHp[i] << "\n";
            }
        }
        std::cout << "\n\n";
        std::cout << hero.name() << " | "
                  << "hp: " << hero.hitpoints() << "\n";

        char choice = '0';
        while (choice <= '0' || choice >= '4') {
            std::cout << "1. Fight, 2. Run, 3. Use item\n\n";
            std::cin >> choice;
            std::cin.ignore(10000, '\n');
        }

        switch (choice) {
        case '1': {
            std::cout << "Which monster do you want to attack? ";

            char monsterChoice = 0;
            do {
                std::cin >> monsterChoice;
                std::cin.ignore(10000, '\n');
            } while ((monsterChoice < '0' || monsterChoice > (numMonsters - 1) + '0')
                && monsterHp[monsterChoice - '0'] <= 0);

            const int monsterToFight = monsterChoice - '0';

            if (monsterHp[monsterToFight] > 0) {
                const int heroAttack = hero.attack();
                std::cout << "\nYou hit the monster for " << heroAttack << "dmg\n";

                const int newMonsterHp = monsterHp[monsterToFight] - heroAttack;
                if (monsterHp[monsterToFight] > 0 && newMonsterHp <= 0) {
                    std::cout << "You've killed " << monsters[monsterToFight]->name() << "\n";
                    ExperienceSystem::instance().addExperience(hero, *monsters[monsterToFight]);
                    std::cout << "\n";
                    monsterHp[monsterToFight] = newMonsterHp;
                }
            }

            for (int i = 0; i < numMonsters; ++i) {
                if (monsterHp[i] <= 0)
                    continue;

                for (int j = 0; j < monsters[i]->attackProbability().hitRepeats; ++j) {
                    if ((RNG::generate(0, 100) < monsters[i]->attackProbability().hitPercentage - hero.defence())) {
                        const int monsterAttack = RNG::generate(monsters[i]->damage().minimum, monsters[i]->damage().maximum);
                        std::cout << "You get hit for " << monsterAttack << " damage.\n";
                        hero.setHitpoints(hero.hitpoints() - monsterAttack);
                    } else {
                        std::cout << monsters[i]->name() << " tries to attack but misses.\n";
                    }
                }
            }

        } break;
        case '2': {
            std::cout << "You run away in direction: (w,a,s,d): ";
            char input;
            std::cin >> input;
            std::cin.ignore(10000, '\n');

            // 50% chance to run
            if (RNG::generate(0, 100) >= 50) {
                TravelSystem::instance().travel(input, hero, layer);
                std::cout << "\n\n\n";
                delete[] monsterHp;
                return;
            }
            std::cout << "You failed to run away.\n\n";
        } break;
        case '3': {
        } break;
        default:
            break;
        }
    }
    delete[] monsterHp;
}

void FightSystem::fightBoss(Hero& hero, Monster& monster, DungeonLayer& layer)
{
    int monsterHp = monster.hitpoints();

    while (hero.hitpoints() > 0 && monsterHp > 0) {
        std::cout << "\n\n";
        std::cout << hero.name() << " | "
                  << "hp: " << hero.hitpoints() << "\n";
        std::cout << monster.name() << " | "
                  << "hp: " << monsterHp << "\n\n";

        char choice = '0';
        while (choice <= '0' || choice >= '3') {
            std::cout << "1. Fight, 2. Use item\n\n";
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

            if (monsterHp <= 0) {
                std::cout << "You've killed " << monster.name() << "\n";
                ExperienceSystem::instance().addExperience(hero, monster);
                layer.nextLayer();
            }
        } break;
        case '2': {
            InventorySystem::instance().use(hero, monster);
        } break;
        default:
            break;
        }
    }
}
