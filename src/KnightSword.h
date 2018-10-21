#pragma once
#include "Item.h"

class KnightSword : public Item {
    int m_damage = 12;

public:
    KnightSword();
    ~KnightSword() override = default;

    const char* description() override;
    bool use(Hero& hero) override;
    bool use(Monster& monster) override;
};
