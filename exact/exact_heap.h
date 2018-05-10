// exact_heap.h
#pragma once

#include <cstddef>

namespace exact {

class Cell;

class Heap
{
  public:
    virtual ~Heap();

    virtual const Cell *allocate(std::size_t size) = 0;

    virtual void addRoot(const Cell *root) = 0;

    virtual void removeRoot(const Cell *root) = 0;

    virtual void addReference(const Cell *from, const Cell *to) = 0;

    virtual void removeReference(const Cell *from, const Cell *to) = 0;
};

}

