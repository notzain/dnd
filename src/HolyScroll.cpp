#include "HolyScroll.h"
#include "Hero.h"
#include "Monster.h"

#include <iostream>

HolyScroll::HolyScroll()
    : Item("Holy Scroll")
{
}

bool HolyScroll::use(Hero& hero)
{
    std::cout << "The scroll has no effects on kind-hearted beings.\n";
    return false;
}

bool HolyScroll::use(Monster& monster)
{
    std::cout << "The scroll shines brightly. It does 300 damage.\n";
    monster.setHitpoints(monster.hitpoints() - 300);
    return true;
}

const char* HolyScroll::description()
{
    return "A magic scroll blessed by the Holy Church.\n";
}
