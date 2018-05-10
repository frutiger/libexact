// exact_cell.cpp
#include <exact_cell.h>

namespace exact {

Cell::Cell(void *object)
: d_address_p(new std::uintptr_t)
{
    *d_address_p = reinterpret_cast<std::uintptr_t>(object);
}

Cell::~Cell()
{
    delete d_address_p;
}

uintptr_t Cell::address() const
{
    return *d_address_p;
}

void *Cell::object() const
{
    return reinterpret_cast<void *>(*d_address_p);
}

bool operator<(const Cell& lhs, const Cell& rhs)
{
    return lhs.object() < rhs.object();
}

bool operator<(const Cell& lhs, void *rhsObject)
{
    return lhs.object() < rhsObject;
}

bool operator<(void *lhsObject, const Cell& rhs)
{
    return lhsObject < rhs.object();
}

}

