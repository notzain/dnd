#pragma once
#include "Item.h"

class KnightSword : public Item {
    bool m_isEquipped;
    int m_damage = 4;

public:
    KnightSword();
    ~KnightSword() override = default;

    const char* description() override;
    bool use(Hero& hero) override;
    bool use(Monster& monster) override;
};
