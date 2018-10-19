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
        auto* lowestMonster = std::find_if(layer.config().monsters->array, layer.config().monsters->array + layer.config().monsters->length, [&](const Monster* monster) {
            return static_cast<int>(monster->level()) == layer.config().minEnemyLevel;
        });
        auto* highestMonster = std::find_if(layer.config().monsters->array, layer.config().monsters->array + layer.config().monsters->length, [&](const Monster* monster) {
            return static_cast<int>(monster->level()) == layer.config().maxEnemyLevel;
        });

        auto* monster = lowestMonster + RNG::generate(0, (highestMonster - lowestMonster));
        FightSystem::instance().fight(hero, **monster, layer);
    }
}