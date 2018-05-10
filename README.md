libexact
========

A library that abstracts an exact moving garbage collector, and provides
implementations.

The major components are heaps and cells.  Ancillary utility components, cell
holder, root and reference are provided for convenience.

Heaps
-----

Heaps are responsible for managing the memory and lifetimes of Cells allocated
from it.  It is expected that cells from a heap can only be rooted in that heap
and can only refer to other cells from that heap.  In other words, each heap is
likely its own isolated world.  However, heap implementations may allow
transfer of cells.

Heaps may be used as template parameters or via a type erased
`exact::TypeErasedHeap` implementation which invokes all operations via a
virtual table `exact::Heap`.

A poorly optimized but functional heap implementation is provided
`exact::NonMovingMarkSweep`.

Cells
-----

A cell is a class template `exact::Cell<T>` that is a relocatable buffer of
adequate size to fit an object of the template parameter.  Holding the buffer
is incorrect as it may be relocated by the heap at any time.

Roots & References
------------------

Rooted cells `exact::Root` form the root set and may not be destroyed.  For
convenience, a rooted cell can be used as a Cell would.  `exact::RootUtil` is
provided to conviently create rooted cells.

Cells may be referenced `exact::Reference` by other cells.  The transitive
closure of the root set using reference as the operation may not be destroyed.
For convenience, a referenced cell can be used as a Cell would.
`exact::ReferenceUtil` is provided to conviently create referenced cells.

