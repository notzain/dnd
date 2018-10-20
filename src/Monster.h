#ifndef DND_MONSTER_H
#define DND_MONSTER_H

#include "RNG.h"
#include <algorithm>

struct AttackProbability {
    int hitPercentage;
    int hitRepeats;
};

struct Damage {
    int minimum;
    int maximum;
};

enum class Level {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    BOSS
};

class Monster {
    char* m_name;
    Level m_level;
    AttackProbability m_attackProbability;
    Damage m_damage;
    int m_defencePercentage;
    int m_hitpoints;

public:
    Monster(const char* name, Level level, const AttackProbability& attackProbability, const Damage& damage,
        int defencePercentage, int hitpoints);

    virtual ~Monster();

    const char* name() const;
    void setName(const char* name);

    Level level() const;
    void setLevel(Level level);

    const AttackProbability& attackProbability() const;
    void setAttackProbability(const AttackProbability& attackProbability);

    const Damage& damage() const;
    void setDamage(const Damage& damage);

    int defencePercentage() const;
    void setDefencePercentage(int defencePercentage);

    int hitpoints() const;
    void setHitpoints(int hitpoints);
};

struct MonsterArray {
    Monster** array{};
    std::size_t length{};

    virtual ~MonsterArray()
    {
        for (int i = 0; i < length; ++i) {
            delete array[i];
        }
        delete[] array;
    }

    Monster* randomMonsterWithLevel(int level)
    {
        auto* firstMonster = *std::find_if(array, array + length, [&](const Monster* monster) {
            return static_cast<int>(monster->level()) == level;
        });
        auto end = std::find_if(std::reverse_iterator<Monster**>(array + length), std::reverse_iterator<Monster**>(array), [&](const Monster* monster) {
            return static_cast<int>(monster->level()) == level;
        });
        auto* lastMonster = *end;

        auto* monster = firstMonster + RNG::generate(0, (lastMonster - firstMonster));
        return monster;
    }

    Monster* randomMonsterInRange(int minLevel, int maxLevel)
    {
        auto* lowestMonster = std::find_if(array, array + length, [&](const Monster* monster) {
            return static_cast<int>(monster->level()) == minLevel;
        });
        auto* highestMonster = std::find_if(array, array + length, [&](const Monster* monster) {
            return static_cast<int>(monster->level()) == maxLevel;
        });

        auto* monster = lowestMonster + RNG::generate(0, (highestMonster - lowestMonster));
        return *monster;
    }
};

#endif // DND_MONSTER_H
