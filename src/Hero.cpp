#include "Hero.h"
#include <cstring>

Hero::Hero(const char* name, int level, int hitpoints, int exp, int attack, int defence)
    : m_name(nullptr)
    , m_level(level)
    , m_hitpoints(hitpoints)
    , m_exp(exp)
    , m_attack(attack)
    , m_defence(defence)
{
    setName(name);
}

Hero::~Hero()
{
    delete[] m_name;
}

const char* Hero::name() const
{
    return m_name;
}

void Hero::setName(const char* name)
{
    delete[] m_name;

    const std::size_t nameLength = strlen(name);
    m_name = new char[nameLength + 1];
    strcpy(m_name, name);
}

int Hero::level() const
{
    return m_level;
}

void Hero::setLevel(int level)
{
    m_level = level;
}

int Hero::hitpoints() const
{
    return m_hitpoints;
}

void Hero::setHitpoints(int hitpoints)
{
    m_hitpoints = hitpoints;
    if (m_hitpoints > MAX_HP) {
        m_hitpoints = MAX_HP;
    }
}

int Hero::exp() const
{
    return m_exp;
}

void Hero::setExp(int exp)
{
    m_exp = exp;
}

int Hero::attack() const
{
    return m_attack;
}

void Hero::setAttack(int attack)
{
    m_attack = attack;
}

int Hero::defence() const
{
    return m_defence;
}

void Hero::setDefence(int defence)
{
    m_defence = defence;
}

Inventory& Hero::inventory()
{
    return m_inventory;
}

int Hero::x() const
{
    return m_x;
}

void Hero::setX(int x)
{
    m_x = x;
}

int Hero::y() const
{
    return m_y;
}

void Hero::setY(int y)
{
    m_y = y;
}
