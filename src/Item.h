#ifndef DND_ITEM_H
#define DND_ITEM_H

#include <cstddef>
#include <cstring>

class Hero;
class Monster;
class Item {
    char* m_name{};

public:
    Item(const char* name)
        : m_name(nullptr)
    {
        setName(name);
    }

    virtual ~Item()
    {
        delete[] m_name;
    }

    const char* name() const
    {
        return m_name;
    }

    void setName(const char* name)
    {
        delete m_name;

        const std::size_t nameLength = strlen(name);
        m_name = new char[nameLength + 1];
        strcpy(m_name, name);
    }

    virtual void use(Hero& hero) = 0;
    virtual void use(Monster& monster) = 0;
};

#endif //DND_ITEM_H
