// app.m.cpp

#include <exact_cell.h>
#include <exact_nonmovingmarksweep.h>
#include <exact_root.h>
#include <exact_reference.h>
#include <exact_typeerasedheap.h>
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
    using namespace exact;
    using namespace std;

    int testCase = 0;
    if (argc >= 2) {
        istringstream arg2(argv[1]);
        arg2 >> testCase;
    }

    switch (testCase) {
      case 0:
      case 5: {
        NonMovingMarkSweep heap;
        auto x1 = RootUtil::create<int>(&heap, 5);
        auto x2 = ReferenceUtil::create<int>(&heap, x1, 10);
        heap.markAndSweep();
        cout << x1.as<int>() * x2.as<int>() << '\n';
      } break;

      case 4: {
        NonMovingMarkSweep heap;
        auto x1 = RootUtil::create<int>(&heap, 5);
        auto x2 = RootUtil::create<int>(&heap, 10);
        heap.markAndSweep();
        cout << x1.as<int>() * x2.as<int>() << '\n';
      } break;

      case 3: {
        NonMovingMarkSweep heap;
        auto x1 = RootUtil::create<int>(&heap, 5);
        heap.markAndSweep();
        cout << x1.as<int>() << '\n';
      } break;

      case 2: {
        NonMovingMarkSweep                 concreteHeap;
        TypeErasedHeap<NonMovingMarkSweep> heap(&concreteHeap);
        auto x1 = Cell::create<int>(&heap, 5);
      } break;

      case 1:{
        NonMovingMarkSweep heap;
        auto x1 = Cell::create<int>(&heap, 5);
      } break;
    }
}

