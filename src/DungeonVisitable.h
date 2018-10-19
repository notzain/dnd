#ifndef DND_DUNGEONVISITABLE_H
#define DND_DUNGEONVISITABLE_H

#include <cstddef>
#include <cstring>
#include <iosfwd>

class DungeonVisitable {
    char* m_description{};

protected:
    bool m_isVisited = false;

public:
    explicit DungeonVisitable(const char* description)
    {
        const std::size_t descriptionLength = strlen(description);
        m_description = new char[descriptionLength + 1];
        strcpy(m_description, description);
    }

    virtual ~DungeonVisitable()
    {
        delete[] m_description;
    }

    const char* description() const
    {
        return m_description;
    }

    bool isVisited() const
    {
        return m_isVisited;
    }

    virtual void visit() = 0;
    virtual void printSymbol(std::ostream& str) = 0;
    virtual void printHorizontalNeighbour(std::ostream& str) = 0;
    virtual void printVerticalNeighbour(std::ostream& str) = 0;
};

#endif //DND_DUNGEONVISITABLE_H
