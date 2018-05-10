// exact_typeerasedheap.h
#pragma once

#include <exact_heap.h>
#include <cstddef>

namespace exact {

class Cell;

template <class HEAP>
class TypeErasedHeap : public Heap {
    HEAP *d_heap_p;

  public:
    explicit TypeErasedHeap(HEAP *heap);

    const Cell *allocate(std::size_t size) override;

    void addRoot(const Cell *object) override;

    void removeRoot(const Cell *object) override;

    void addReference(const Cell *from, const Cell *to) override;

    void removeReference(const Cell *from, const Cell *to) override;
};

template <class HEAP>
TypeErasedHeap<HEAP>::TypeErasedHeap(HEAP *heap)
: d_heap_p(heap)
{
}

template <class HEAP>
const Cell *TypeErasedHeap<HEAP>::allocate(std::size_t size)
{
    return d_heap_p->allocate(size);
}

template <class HEAP>
void TypeErasedHeap<HEAP>::addRoot(const Cell *object)
{
    return d_heap_p->addRoot(object);
}

template <class HEAP>
void TypeErasedHeap<HEAP>::removeRoot(const Cell *object)
{
    return d_heap_p->removeRoot(object);
}

template <class HEAP>
void TypeErasedHeap<HEAP>::addReference(const Cell *from, const Cell *to)
{
    return d_heap_p->addReference(from, to);
}

template <class HEAP>
void TypeErasedHeap<HEAP>::removeReference(const Cell *from, const Cell *to)
{
    return d_heap_p->removeReference(from, to);
}

}

