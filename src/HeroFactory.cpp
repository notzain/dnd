#include "HeroFactory.h"
#include "Hero.h"
#include "SaveSystem.h"
#include <bits/exception.h>
#include <iostream>

Hero* HeroFactory::makeFromFile(const char* filename) const
{
    Hero* hero = new Hero("", 0, 0, 0, 0, 0);

    try {
        SaveSystem::instance().load(*hero, filename);
        return hero;
    } catch (const std::exception& e) {
        std::cerr << "Could not make hero from file.\n";
        return nullptr;
    }
}

Hero* HeroFactory::makeDefaultHero() const
{
    char name[32];
    std::cout << "Enter Hero's name: ";
    std::cin >> name;
    std::cin.ignore(10000, '\n');

    return new Hero(name, 1, 100, 0, 8, 5);
}
