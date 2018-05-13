// exact_nonmovingmarksweep.cpp
#include <exact_nonmovingmarksweep.h>

#include <exact_cell.h>
#include <cstdlib>
#include <deque>
#include <new>
#include <vector>

namespace exact {

void NonMovingMarkSweep::deallocate(const Cell *cell)
{
    std::free(cell->object());
    d_cells.erase(*cell);
}

NonMovingMarkSweep::~NonMovingMarkSweep()
{
    markAndSweep();
}

const Cell *NonMovingMarkSweep::allocate(std::size_t size)
{
    void *object = std::malloc(size);
    if (!object) {
        throw std::bad_alloc();
    }

    return &*d_cells.emplace(object).first;
}

void NonMovingMarkSweep::addRoot(const Cell *root)
{
    d_roots.insert(root);
}

void NonMovingMarkSweep::removeRoot(const Cell *root)
{
    d_roots.erase(root);
}

void NonMovingMarkSweep::addReference(const Cell *from, const Cell *to)
{
    d_references.insert(Edge(from, to));
}

void NonMovingMarkSweep::removeReference(const Cell *from, const Cell *to)
{
    d_references.erase(Edge(from, to));
}

void NonMovingMarkSweep::markAndSweep()
{
    std::set<const Cell *> marked;

    std::deque<const Cell *> queue(d_roots.begin(), d_roots.end());
    while (!queue.empty()) {
        const Cell *object = queue.front();
        queue.pop_front();

        marked.insert(object);

        std::vector<Edge> references;
        auto begin = d_references.lower_bound(Edge(object,     0));
        auto end   = d_references.upper_bound(Edge(object + 1, 0));
        std::copy_if(begin, end,
                     std::back_inserter(references),
                     [&marked] (auto&& edge) {
                         return marked.count(edge.second) == 0;
                     });
        std::transform(references.begin(), references.end(),
                       std::back_inserter(queue),
                       [](auto&& edge) {
                           return edge.second;
                       });
    }

    std::vector<const Cell *> unreferenced;

    std::vector<const Cell *> cells;
    std::transform(d_cells.begin(), d_cells.end(),
                   std::back_inserter(cells),
                   [](auto&& cell) {
                       return &cell;
                   });

    std::set_difference(cells.begin(),  cells.end(),
                        marked.begin(), marked.end(),
                        std::back_inserter(unreferenced));

    std::for_each(unreferenced.begin(), unreferenced.end(),
                  [this] (auto&& cell) {
                      deallocate(cell);
                  });
}

}

