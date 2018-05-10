// exact_reference.h
#pragma once

#include <exact_cellholder.h>
#include <utility>

namespace exact {

template <class HEAP>
class Reference : public CellHolder
{
    HEAP       *d_heap_p;
    const Cell *d_from_p;

  public:
    Reference(HEAP *heap, const Cell *from, const Cell *to);
    ~Reference();

    Reference(const Reference& other) = delete;
    Reference& operator=(const Reference& other) = delete;
};

struct ReferenceUtil
{
    template <class T, class HEAP, class... ARGS>
    static Reference<HEAP> create(HEAP       *heap,
                                  const Cell *from,
                                  ARGS&&...   args);
};

template <class T, class HEAP, class... ARGS>
Reference<HEAP> ReferenceUtil::create(HEAP       *heap,
                                      const Cell *from,
                                      ARGS&&...   args)
{
    return Reference<HEAP>(heap,
                           from,
                           Cell::create<int>(
                                        heap,
                                        std::forward<ARGS...>(args...)));
}

template <class HEAP>
Reference<HEAP>::Reference(HEAP *heap, const Cell *from, const Cell *to)
: CellHolder(to)
, d_heap_p(heap)
, d_from_p(from)
{
    d_heap_p->addReference(d_from_p, *this);
}

template <class HEAP>
Reference<HEAP>::~Reference()
{
    d_heap_p->removeReference(d_from_p, *this);
}

}

