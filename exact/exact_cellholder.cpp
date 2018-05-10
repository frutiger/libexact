// exact_cellholder.cpp
#include <exact_cellholder.h>

namespace exact {

CellHolder::CellHolder(const Cell *cell)
: d_cell_p(cell)
{
}

CellHolder::operator const Cell *() const
{
    return d_cell_p;
}

}

