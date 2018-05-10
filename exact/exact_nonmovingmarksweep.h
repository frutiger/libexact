// exact_nonmovingmarksweep.h
#pragma once

#include <set>

namespace exact {

class Cell;

class NonMovingMarkSweep
{
    using Edge = std::pair<const Cell *, const Cell *>;

    std::set<Cell>              d_cells;
    std::multiset<const Cell *> d_roots;
    std::multiset<Edge>         d_references;

    void deallocate(const Cell *cell);

  public:
    explicit NonMovingMarkSweep() = default;
    NonMovingMarkSweep(const NonMovingMarkSweep&) = delete;
    NonMovingMarkSweep& operator=(const NonMovingMarkSweep&) = delete;
    ~NonMovingMarkSweep();

    const Cell *allocate(std::size_t size);

    void addRoot(const Cell *root);

    void removeRoot(const Cell *root);

    void addReference(const Cell *from, const Cell *to);

    void removeReference(const Cell *from, const Cell *to);

    void markAndSweep();
};

}

