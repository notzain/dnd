#include "InventorySystem.h"
#include "Hero.h"
#include "Item.h"
#include "Monster.h"

#include <iostream>

InventorySystem& InventorySystem::instance()
{
    static InventorySystem inventorySystem;
    return inventorySystem;
}

void InventorySystem::use(Hero& hero, Monster& monster)
{
    std::cout << "You look inside your bag.\n";
    bool hasItem = false;
    for (int i = 0; i < hero.inventory().itemCount(); ++i) {
        auto* item = hero.inventory().getItem(i);
        if (item != nullptr) {
            std::cout << i << ": " << item->description() << "\n";
            hasItem = true;
        }
    }
    if (!hasItem) {
        std::cout << "You have no items.\n\n";
        return;
    }
    std::cout << "What do you do? Nothing (0) | Use item (1): ";
    char choice = 0;
    std::cin >> choice;
    std::cin.ignore(1000, '\n');
    std::cout << "\n\n";

    if (choice == '1') {
        std::cout << "What item do you want to use? ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');
        std::cout << "\n";

        char self = 0;
        std::cout << "Use on self? (y/n)";
        std::cin >> self;
        std::cin.ignore(1000, '\n');

        auto* item = hero.inventory().getItem(choice - '0');
        if (item != nullptr) {
            if (self == 'y') {
                if (item->use(hero)){
                    std::cout << "The item becomes unusable.\n";
                    hero.inventory().removeItem(item);
                };
            } else if (self == 'n') {
                if (item->use(monster)){
                    std::cout << "The item becomes unusable.\n";
                    hero.inventory().removeItem(item);
                };
            }
        }
    }
}

void InventorySystem::use(Hero& hero)
{
    std::cout << "You look inside your bag.\n";
    bool hasItem = false;
    for (int i = 0; i < hero.inventory().itemCount(); ++i) {
        auto* item = hero.inventory().getItem(i);
        if (item != nullptr) {
            std::cout << i << ": " << item->description() << "\n";
            hasItem = true;
        }
    }
    if (!hasItem) {
        std::cout << "You have no items.\n\n";
        return;
    }
    std::cout << "What do you do? Nothing (0) | Use item (1): ";
    char choice = 0;
    std::cin >> choice;
    std::cin.ignore(1000, '\n');
    std::cout << "\n\n";

    if (choice == '1') {
        std::cout << "What item do you want to use? ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');
        std::cout << "\n";

        auto* item = hero.inventory().getItem(choice - '0');
        if (item != nullptr) {
            if (item->use(hero)){
                std::cout << "The item becomes unusable.\n";
                hero.inventory().removeItem(item);
            };
        }
    }
}
