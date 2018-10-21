#ifndef DND_ITEM_H
#define DND_ITEM_H

#include <cstddef>
#include <cstring>

class Hero;
class Monster;
class Item {
    char* m_name{};

protected:
    bool m_isEquipped;

public:
    explicit Item(const char* name)
        : m_name(nullptr)
        , m_isEquipped(false)
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

    bool isEquipped() const
    {
        return m_isEquipped;
    }

    virtual const char* description() = 0;
    virtual bool use(Hero& hero) = 0;
    virtual bool use(Monster& monster) = 0;
};

#endif //DND_ITEM_H
