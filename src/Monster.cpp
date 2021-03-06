#include "Monster.h"

#include <cstddef>
#include <cstring>
#include <string>

Monster::Monster(const char* name, Level level, const AttackProbability& attackProbability, const Damage& damage,
    int defencePercentage, int hitpoints)
    : m_name(nullptr)
    , m_level(level)
    , m_attackProbability(attackProbability)
    , m_damage(damage)
    , m_defencePercentage(defencePercentage)
    , m_hitpoints(hitpoints)
{
    setName(name);
}

Monster::~Monster()
{
    delete[] m_name;
}

const char* Monster::name() const
{
    return m_name;
}

void Monster::setName(const char* name)
{
    delete m_name;

    const std::size_t nameLength = strlen(name);
    m_name = new char[nameLength + 1];
    strcpy(m_name, name);
}

Level Monster::level() const
{
    return m_level;
}

void Monster::setLevel(const Level level)
{
    m_level = level;
}

const AttackProbability& Monster::attackProbability() const
{
    return m_attackProbability;
}

void Monster::setAttackProbability(const AttackProbability& attackProbability)
{
    m_attackProbability = attackProbability;
}

const Damage& Monster::damage() const
{
    return m_damage;
}

void Monster::setDamage(const Damage& damage)
{
    m_damage = damage;
}

int Monster::defencePercentage() const
{
    return m_defencePercentage;
}

void Monster::setDefencePercentage(int defencePercentage)
{
    m_defencePercentage = defencePercentage;
}

int Monster::hitpoints() const
{
    return m_hitpoints;
}

void Monster::setHitpoints(int hitpoints)
{
    m_hitpoints = hitpoints;
}

/*
    this functions is wrong
    it actually picks a random monster from 'level' to the end of the array
    currently works cause we only use it to find a random boss...
*/
Monster* MonsterArray::randomMonsterWithLevel(int level)
{
    int firstMonsterIndex = 0;
    for (; firstMonsterIndex < length; firstMonsterIndex++) {
        if (array[firstMonsterIndex]->level() == Level::BOSS) {
            break;
        }
    }

    auto* monster = array[RNG::generate(firstMonsterIndex, static_cast<int>(length - 1))];
    return monster;
}

Monster* MonsterArray::randomMonsterInRange(int minLevel, int maxLevel)
{
    auto* lowestMonster = std::find_if(array, array + length, [&](const Monster* monster) {
        return static_cast<int>(monster->level()) == minLevel;
    });
    auto* highestMonster = std::find_if(array, array + length, [&](const Monster* monster) {
        return static_cast<int>(monster->level()) == maxLevel;
    });

    // pointer math
    // if lowestmonster is X, and highestmonster is Y
    // every monster between X and Y fits the description
    // distance between X and Y is mem address of Y - mem address of X

    // so pick a random monster starting from X, ending at Y
    auto* monster = lowestMonster + RNG::generate(0, (highestMonster - lowestMonster));
    return *monster;
}

MonsterArray::~MonsterArray()
{
    for (int i = 0; i < length; ++i) {
        delete array[i];
    }
    delete[] array;
}
