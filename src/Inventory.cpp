#include "Inventory.h"
#include "Item.h"
#include <stdexcept>

Inventory::Inventory() {
    for (auto &m_item : m_items) {
        m_item = nullptr;
    }
};

Inventory::~Inventory()
{
    for (auto &m_item : m_items) {
        delete m_item;
    }
}

Item* Inventory::getItem(std::size_t index) const
{
    if (index > 3 || index < 0 || index > m_slot) {
        throw std::runtime_error("Invalid index length.");
    }

    return m_items[index];
}

void Inventory::addItem(Item* item)
{
    if (m_slot > 3) {
    }
    m_items[m_slot] = item;
}
