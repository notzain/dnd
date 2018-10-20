#include "Inventory.h"
#include "Item.h"
#include <stdexcept>

Inventory::Inventory()
{
    for (auto& m_item : m_items) {
        m_item = nullptr;
    }
};

Inventory::~Inventory()
{
    for (auto* m_item : m_items) {
        delete m_item;
    }
}

Item* Inventory::getItem(std::size_t index) const
{
    if (index < 0 || index > MAX_ITEMS) {
        throw std::runtime_error("Invalid item index.");
    }
    return m_items[index];
}

bool Inventory::addItem(Item* item)
{
    for (auto &m_item : m_items) {
        if (m_item == nullptr) {
            m_item = item;
            return true;
        }
    }
    return false;
}

void Inventory::removeItem(Item* item)
{
    for (auto &m_item : m_items) {
        if (m_item == item) {
            delete m_item;
            m_item = nullptr;
        }
    }
}
