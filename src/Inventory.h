#ifndef DND_INVENTORY_H
#define DND_INVENTORY_H

#include <cstddef>

class Item;
class Inventory {
    Item* m_items[3];
    int m_slot{};

public:
    Inventory();
    virtual ~Inventory();
    void addItem(Item* item);
    Item* getItem(std::size_t index) const;
};

#endif //DND_INVENTORY_H
