// exact_cell.h
#pragma once

#include <cstdint>
#include <utility>

namespace exact {

class Cell {
    std::uintptr_t *d_address_p;

  public:
    template <class T, class HEAP, class... ARGS>
    static const Cell *create(HEAP *heap, ARGS&&... args);

    Cell(void *object);
    Cell(const Cell&) = delete;
    Cell& operator=(const Cell&) = delete;
    ~Cell();

    std::uintptr_t address() const;
    void *object() const;

    template <class T>
    T& as() const;
};

bool operator<(const Cell&  lhs,       const Cell&  rhs);
bool operator<(const Cell&  lhs,       void        *rhsObject);
bool operator<(void        *lhsObject, const Cell&  rhs);

template <class T, class HEAP, class... ARGS>
const Cell *Cell::create(HEAP *heap, ARGS&&... args)
{
    const Cell *cell   = heap->allocate(sizeof(T));
    void       *object = cell->object();

    new (object) T(std::forward<ARGS...>(args...));
    return cell;
}

template <class T>
T& Cell::as() const
{
    return *static_cast<T *>(object());
}

}

