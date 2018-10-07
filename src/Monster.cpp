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
