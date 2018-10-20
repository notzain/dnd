#ifndef DND_DUNGEONVISITABLE_H
#define DND_DUNGEONVISITABLE_H

#include <cstddef>
#include <cstring>
#include <iosfwd>

class DungeonVisitable {
    char* m_description{};

protected:
    bool m_isVisited = false;
    int m_x{},
        m_y{};

public:
    explicit DungeonVisitable(const char* description, int x, int y)
        : m_x(x)
        , m_y(y)
    {
        const std::size_t descriptionLength = strlen(description);
        m_description = new char[descriptionLength + 1];
        strcpy(m_description, description);
    }

    int x() const
    {
        return m_x;
    }

    void setX(int x)
    {
        m_x = x;
    }

    int y() const
    {
        return m_y;
    }

    void setY(int y)
    {
        m_y = y;
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

    void setAsStart()
    {
        m_isVisited = true;
    }

    virtual void visit() = 0;
    virtual void printSymbol(std::ostream& str) = 0;
    virtual void printHorizontalNeighbour(std::ostream& str) = 0;
    virtual void printVerticalNeighbour(std::ostream& str) = 0;
};

#endif //DND_DUNGEONVISITABLE_H
