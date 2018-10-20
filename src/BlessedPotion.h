#pragma once

#include "Item.h"

class BlessedPotion : public Item{
public:
    BlessedPotion();
    ~BlessedPotion() override = default;

    const char *description() override;

    bool use(Hero &hero) override;

    bool use(Monster &monster) override;


};


