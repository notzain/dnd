#include "BlessedPotion.h"
#include "Hero.h"
#include "Monster.h"
#include <iostream>

BlessedPotion::BlessedPotion()
    : Item("Blessed Potion")
{
}

const char* BlessedPotion::description()
{
    return "A potion blessed by an Archmage. Heals 80 hp.\n";
}

bool BlessedPotion::use(Hero& hero)
{
    std::cout << "You drink the potion. You feel refreshed. (+80 hp)\n";
    hero.setHitpoints(hero.hitpoints() + 80);
    return true;
}

bool BlessedPotion::use(Monster& monster)
{
    if (monster.level() == Level::BOSS) {
        std::cout << "You throw the potion at the monster. Supringly, it does 80 dmg.\n";
        monster.setHitpoints(monster.hitpoints() - 80);
    } else {
        std::cout << "You are either a really kind person, or an idiot. Or both.\n You heal the monster. (+80 hp)\n";
        monster.setHitpoints(monster.hitpoints() + 80);
    }
    return true;
}
