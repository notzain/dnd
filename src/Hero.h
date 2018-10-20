#ifndef DND_HERO_H
#define DND_HERO_H

#include "Inventory.h"

class Hero {
    static const int MAX_HP = 100;

    char* m_name;
    int m_level;
    int m_hitpoints;
    int m_exp;
    int m_attack;
    int m_defence;
    Inventory m_inventory;

    int m_x;
    int m_y;

public:
    Hero(const char* name, int level, int hitpoints, int exp, int attack, int defence);
    virtual ~Hero();

    const char* name() const;
    void setName(const char* name);

    int level() const;
    void setLevel(int level);

    int hitpoints() const;
    void setHitpoints(int hitpoints);

    int exp() const;
    void setExp(int exp);

    int attack() const;
    void setAttack(int attack);

    int defence() const;
    void setDefence(int defence);

    Inventory& inventory();

    int x() const;
    void setX(int x);
    
    int y() const;
    void setY(int y);

};

#endif //DND_HERO_H
