#pragma once

#include <cstddef>

class Hero;
class Monster;
class DungeonLayer;

class FightSystem {
    FightSystem() = default;
    FightSystem(const FightSystem&) = default; // Copy constructor
    FightSystem(FightSystem&&) = default; // Move constructor
    FightSystem& operator=(const FightSystem&) = default; // Copy assignment operator
    FightSystem& operator=(FightSystem&&) = default; // Move assignment operator
    virtual ~FightSystem() = default; // Destructor

public:
    static FightSystem& instance();
    void fight(Hero& hero, Monster& monster, DungeonLayer& layer);
    void fight(Hero& hero, Monster** monster, std::size_t numMonsters, DungeonLayer& layer);
};
