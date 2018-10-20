#pragma once

#include "Item.h"

class Potion : public Item {
public:
    Potion();
    ~Potion() override = default;

    const char *description() override;
    bool use(Hero &hero) override;
    bool use(Monster &monster) override;
};


