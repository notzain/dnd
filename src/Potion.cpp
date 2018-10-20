#include "Potion.h"
#include "Hero.h"
#include "Monster.h"
#include <iostream>

Potion::Potion()
    : Item("Common potion")
{
}

const char* Potion::description()
{
    return "A common potion bought from a stall. (heals 10 hp)\n";
}

bool Potion::use(Hero& hero)
{
    std::cout << "You drink the potion. It tastes bitter. (+10 hp)\n";
    hero.setHitpoints(hero.hitpoints() + 10);
    return true;
}

bool Potion::use(Monster& monster)
{
    std::cout << "You are either a really kind person, or an idiot. Or both.\n You heal the monster. (+10 hp)\n";
    monster.setHitpoints(monster.hitpoints() + 10);
    return true;
}
