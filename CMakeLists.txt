cmake_minimum_required(
    VERSION 3.11
)

add_library(
    exact
    exact/exact_cell.cpp
    exact/exact_cellholder.cpp
    exact/exact_heap.cpp
    exact/exact_nonmovingmarksweep.cpp
    exact/exact_reference.cpp
    exact/exact_root.cpp
    exact/exact_typeerasedheap.cpp
)

target_include_directories(
    exact PUBLIC
    exact
)

add_executable(
    app
    app/app.m.cpp
)

target_link_libraries(
    app
    exact
)

