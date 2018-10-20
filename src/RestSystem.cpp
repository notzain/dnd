#include "RestSystem.h"
#include "DungeonLayer.h"
#include "FightSystem.h"
#include "Hero.h"
#include "Monster.h"
#include "RNG.h"

#include <algorithm>
#include <iostream>

RestSystem& RestSystem::instance()
{
    static RestSystem restSystem;
    return restSystem;
}

void RestSystem::rest(Hero& hero, DungeonLayer& layer)
{
    std::cout << "You take a short break.\n";
    int heal = RNG::generate(9, 16);
    // 40% chance to fight enemy
    if (RNG::generate(0, 100) > 60) {
        auto* monster = layer.config().monsters->randomMonsterInRange(
            layer.config().minEnemyLevel,
            layer.config().maxEnemyLevel);

        FightSystem::instance().fight(hero, *monster, layer);
    }
}