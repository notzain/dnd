#pragma once

#include "Item.h"

class RustySword : public Item {
    bool m_isEquipped;
    int m_damage = 4;
public:
    RustySword();
    ~RustySword() override = default;

    const char* description() override;
    bool use(Hero &hero) override;
    bool use(Monster &monster) override;
};
