#pragma once


#include "Item.h"

class HolyScroll : public Item{
public:
    HolyScroll();
    ~HolyScroll() override = default;

    const char *description() override;

    bool use(Hero &hero) override;
    bool use(Monster &monster) override;

};


