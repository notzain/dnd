#include "RustySword.h"
#include "Hero.h"
#include "Monster.h"

#include <iostream>

RustySword::RustySword()
    : Item("Rusty Sword")
{
}
const char* RustySword::description()
{
    return "A rusted old sword. (4 dmg)\n";
}

bool RustySword::use(Hero& hero)
{
    if (!m_isEquipped) {
        std::cout << "You equip the rusty old sword.\n";
        hero.setAttack(hero.attack() + m_damage);
        m_isEquipped = true;
    } else {
        std::cout << "You unequip the rusty old sword.\n";
        hero.setAttack(hero.attack() - m_damage);
        m_isEquipped = false;
    }
    return false;
}

bool RustySword::use(Monster& monster)
{
    std::cout << "You throw the sword at the monster and pick it up again. It does 1 damage.\n";
    monster.setHitpoints(monster.hitpoints() - 1);
    return false;
}
