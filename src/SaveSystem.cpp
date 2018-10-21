#include "SaveSystem.h"
#include "BlessedPotion.h"
#include "Hero.h"
#include "HolyScroll.h"
#include "Inventory.h"
#include "Item.h"
#include "KnightSword.h"
#include "Potion.h"
#include "RustySword.h"

#include <fstream>
#include <iostream>

enum class Items {
    NONE,
    POT1,
    POT2,
    SWORD1,
    SWORD2,
    SCROLL
};

SaveSystem& SaveSystem::instance()
{
    static SaveSystem saveSystem;
    return saveSystem;
}

void SaveSystem::save(Hero& hero, const char* filename)
{
    std::ofstream fileStream;
    fileStream.exceptions(std::ofstream::failbit);
    try {
        fileStream.open(filename);
    } catch (const std::exception& e) {
        std::cerr << "Could not open file " << filename << "\n";
        throw e;
    }
    // unequip items to get base stats
    bool isEquipped[Inventory::MAX_ITEMS];
    for (int i = 0; i < Inventory::MAX_ITEMS; ++i) {
        auto* item = hero.inventory().getItem(i);
        if (item == nullptr) {
            isEquipped[i] = false;
            continue;
        }
        if (item->isEquipped()) {
            isEquipped[i] = true;
            item->use(hero);
        }
    }

    fileStream << "["
               << hero.name() << ";"
               << hero.level() << ";"
               << hero.hitpoints() << ";"
               << hero.exp() << ";"
               << hero.attack() << ";"
               << hero.defence() << ";"
               << "]\n";

    fileStream << "[";
    for (int i = 0; i < Inventory::MAX_ITEMS; ++i) {
        auto* item = hero.inventory().getItem(i);

        if (item == nullptr) {
            fileStream << "0";
        } else if (dynamic_cast<Potion*>(item)) {
            fileStream << static_cast<int>(Items::POT1);
        } else if (dynamic_cast<BlessedPotion*>(item)) {
            fileStream << static_cast<int>(Items::POT2);
        } else if (dynamic_cast<RustySword*>(item)) {
            fileStream << static_cast<int>(Items::SWORD1);
        } else if (dynamic_cast<KnightSword*>(item)) {
            fileStream << static_cast<int>(Items::SWORD2);
        } else if (dynamic_cast<HolyScroll*>(item)) {
            fileStream << static_cast<int>(Items::SCROLL);
        }
        fileStream << "x" << (isEquipped[i] ? "1" : "0") << ";";
    }
    fileStream << "]\n";

    // re-equip items
    for (int i = 0; i < Inventory::MAX_ITEMS; ++i) {
        auto* item = hero.inventory().getItem(i);
        if (isEquipped[i]) {
            item->use(hero);
        }
    }
}

void SaveSystem::load(Hero& hero, const char* filename)
{
    std::ifstream fileStream;
    fileStream.exceptions(std::ifstream::failbit);
    try {
        fileStream.open(filename);
    } catch (const std::exception& e) {
        std::cerr << "Could not open file " << filename << "\n";
        throw e;
    }

    {
        char line[256];
        fileStream.getline(line, 256);

        char name[32];
        int level;
        int hitpoints;
        int exp;
        int attack;
        int defence;

        sscanf(line, "[%[^;];%d;%d;%d;%d;%d;]\r",
            name, &level, &hitpoints, &exp, &attack, &defence);

        hero.setName(name);
        hero.setLevel(level);
        // if HP is 0, hero has died. reset to 100
        // else, hero is still in a run. use prev hitpoints
        hero.setHitpoints(hitpoints <= 0 ? 100 : hitpoints);
        hero.setExp(exp);
        hero.setAttack(attack);
        hero.setDefence(defence);
    }

    {
        char line[256];
        fileStream.getline(line, 256);
        int items[Inventory::MAX_ITEMS];
        int isEquipped[Inventory::MAX_ITEMS];
        sscanf(line, "[%dx%d;%dx%d;%dx%d;]\r",
            &items[0], &isEquipped[0],
            &items[1], &isEquipped[1],
            &items[2], &isEquipped[2]);

        for (int i = 0; i < Inventory::MAX_ITEMS; ++i) {
            switch (items[i]) {
            case static_cast<int>(Items::POT1): {
                hero.inventory().addItem(new Potion());
            } break;
            case static_cast<int>(Items::POT2): {
                hero.inventory().addItem(new BlessedPotion());
            } break;
            case static_cast<int>(Items::SWORD1): {
                hero.inventory().addItem(new RustySword());
            } break;
            case static_cast<int>(Items::SWORD2): {
                hero.inventory().addItem(new KnightSword());
            } break;
            case static_cast<int>(Items::SCROLL): {
                hero.inventory().addItem(new HolyScroll());
            } break;
            }
            if (isEquipped[i]) {
                hero.inventory().getItem(i)->use(hero);
            }
        }
    }
}
