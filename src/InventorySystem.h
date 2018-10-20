#pragma once

class Hero;
class Monster;

class InventorySystem {
    InventorySystem() = default;
    InventorySystem(const InventorySystem&) = default; // Copy constructor
    InventorySystem(InventorySystem&&) = default; // Move constructor
    InventorySystem& operator=(const InventorySystem&) = default; // Copy assignment operator
    InventorySystem& operator=(InventorySystem&&) = default; // Move assignment operator
    virtual ~InventorySystem() = default; // Destructor

public:
    static InventorySystem& instance();
    void giveRandomItem(Hero& hero);
    void use(Hero& hero, Monster& monster);
    void use(Hero& hero);
};


