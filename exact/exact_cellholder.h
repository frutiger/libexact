// exact_cellholder.h
#pragma once

#include <exact_cell.h>

namespace exact {

class CellHolder {
    const Cell *d_cell_p;

  public:
    explicit CellHolder(const Cell *cell);

    operator const Cell *() const;

    template <class T>
    T& as() const;
};

template <class T>
T& CellHolder::as() const
{
    return d_cell_p->as<T>();
}

}

