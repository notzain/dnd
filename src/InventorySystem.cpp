#include "InventorySystem.h"
#include "BlessedPotion.h"
#include "Hero.h"
#include "HolyScroll.h"
#include "Item.h"
#include "KnightSword.h"
#include "Monster.h"
#include "Potion.h"
#include "RustySword.h"

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

        auto* item = hero.inventory().getItem(choice - '0');
        if (item != nullptr) {
            char self = 0;
            std::cout << "Use on self? (y/n)";
            std::cin >> self;
            std::cin.ignore(1000, '\n');

            if (self == 'y') {
                if (item->use(hero)) {
                    std::cout << "The item becomes unusable.\n";
                    hero.inventory().removeItem(item);
                };
            } else if (self == 'n') {
                if (item->use(monster)) {
                    std::cout << "The item becomes unusable.\n";
                    hero.inventory().removeItem(item);
                };
            }
        } else {
            std::cout << "There is no item like that!\n";
        }
    }
}

void InventorySystem::use(Hero& hero, Monster** monsters, int numMonsters)
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
            char self = 0;
            std::cout << "Use on self? (y/n)";
            std::cin >> self;
            std::cin.ignore(1000, '\n');

            if (self == 'y') {
                if (item->use(hero)) {
                    std::cout << "The item becomes unusable.\n";
                    hero.inventory().removeItem(item);
                };
            } else if (self == 'n') {
                for (int i = 0; i < numMonsters; ++i)  {
                    std::cout << "(" << i << ") " << monsters[i]->name() << "\n";
                }
                std::cout << "What monster do you want to use it on? ";
                char input = 0;
                while ((input < '0' || input > numMonsters - 1 + '0')) {
                    std::cin >> input;
                    std::cin.ignore(1000, '\n');
                }
                if (item->use(*monsters[input - '0'])) {
                    std::cout << "The item becomes unusable.\n";
                    hero.inventory().removeItem(item);
                };
            }
        } else {
            std::cout << "There is no item like that!\n";
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
            std::cout << i << ": " << item->description();
            hasItem = true;
        }
    }
    if (!hasItem) {
        std::cout << "You have no items.\n\n";
        return;
    }
    std::cout << "What do you do? Nothing (0) | Use item (1) | Drop item (2): ";
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
            if (item->use(hero)) {
                std::cout << "The item becomes unusable.\n";
                hero.inventory().removeItem(item);
            };
        }
    } else if (choice == '2') {
        std::cout << "What item do you want to drop? ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');
        std::cout << "\n";

        auto* item = hero.inventory().getItem(choice - '0');
        if (item != nullptr) {
            std::cout << "You drop the item.\n";
            hero.inventory().removeItem(item);
        }
    }
}


void InventorySystem::giveRandomItem(Hero& hero)
{
    Item* itemPtr = nullptr;
    //60% chance to find something
    if (RNG::generate(0, 100) < 60) {
        const int item = RNG::generate(0, 100);
        if (item >= 0 && item < 10) {
            itemPtr = new HolyScroll();
        } else if (item >= 10 && item < 25) {
            itemPtr = new KnightSword();
        } else if (item >= 25 && item < 50) {
            itemPtr = new RustySword();
        } else if (item >= 50 && item < 90) {
            itemPtr = new Potion();
        } else {
            itemPtr = new BlessedPotion();
        }

        std::cout << "You find an item on the ground.\n"
                  << itemPtr->description() << "\n"
                  << "Will you pick it up? (y/n)\n";

        char input;
        std::cin >> input;
        std::cin.ignore(1000, '\n');

        if (input == 'y') {
            if (hero.inventory().addItem(itemPtr)) {
                std::cout << "You keep the item with you.\n";
            } else {
                std::cout << "Your inventory is full. You check your bags.\n";
                use(hero);
                if (hero.inventory().addItem(itemPtr)) {
                    std::cout << "You keep the item with you.\n";
                } else {
                    std::cout << "You leave the item behind.\n";
                    delete itemPtr;
                }
            }
        } else {
            delete itemPtr;
        }
    }
}
