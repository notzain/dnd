#ifndef DND_MONSTER_H
#define DND_MONSTER_H

#include "RNG.h"
#include <algorithm>
#include <iterator>

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

// list of monsters, with helper functions
struct MonsterArray {
    Monster** array{};
    std::size_t length{};

    virtual ~MonsterArray();
    Monster* randomMonsterWithLevel(int level);
    Monster* randomMonsterInRange(int minLevel, int maxLevel);
};

#endif // DND_MONSTER_H
