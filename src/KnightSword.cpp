#include "KnightSword.h"
#include "Hero.h"
#include "Monster.h"
#include <iostream>

KnightSword::KnightSword()
    : Item("Knight's Sword")
{
}

const char* KnightSword::description()
{
    return "A shiny sword used by a knight. (12 dmg)\n";
}

bool KnightSword::use(Hero& hero)
{
    if (!m_isEquipped) {
        std::cout << "You equip the knights sword.\n";
        hero.setAttack(hero.attack() + m_damage);
        m_isEquipped = true;
    } else {
        std::cout << "You unequip the knights sword.\n";
        hero.setAttack(hero.attack() - m_damage);
        m_isEquipped = false;
    }
    return false;
}

bool KnightSword::use(Monster& monster)
{
    std::cout << "You throw the sword at the monster and pick it up again. It does 3 damage.\n";
    monster.setHitpoints(monster.hitpoints() - 3);
    return true;
}
