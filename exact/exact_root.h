// exact_root.h
#pragma once

#include <exact_cellholder.h>
#include <utility>

namespace exact {

template <class HEAP>
class Root : public CellHolder
{
    HEAP *d_heap_p;

  public:
    Root(HEAP *heap, const Cell *cell);
    ~Root();

    Root(const Root& other) = delete;
    Root& operator=(const Root& other) = delete;
};

struct RootUtil
{
    template <class T, class HEAP, class... ARGS>
    static Root<HEAP> create(HEAP *heap, ARGS&&... args);
};

template <class T, class HEAP, class... ARGS>
Root<HEAP> RootUtil::create(HEAP *heap, ARGS&&... args)
{
    return Root<HEAP>(heap,
                      Cell::create<int>(heap,
                                        std::forward<ARGS...>(args...)));
}

template <class HEAP>
Root<HEAP>::Root(HEAP *heap, const Cell *cell)
: CellHolder(cell)
, d_heap_p(heap)
{
    d_heap_p->addRoot(cell);
}

template <class HEAP>
Root<HEAP>::~Root()
{
    d_heap_p->removeRoot(*this);
}

}

