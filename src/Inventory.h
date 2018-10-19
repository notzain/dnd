#ifndef DND_INVENTORY_H
#define DND_INVENTORY_H

#include <cstddef>

class Item;
class Inventory {
    static const int MAX_ITEMS = 3;
    Item* m_items[MAX_ITEMS];

public:
    Inventory();
    virtual ~Inventory();
    void addItem(Item* item);
    Item* getItem(std::size_t index) const;
    void removeItem(Item* item);

    int itemCount() const { return MAX_ITEMS; }
};

#endif //DND_INVENTORY_H
