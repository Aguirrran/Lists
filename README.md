Custom Data Structures in C++

This project implements two core data structures from scratch:

Singly Linked List
Circular Vector (dynamic array with wrapping)

The focus is on understanding memory management, pointers, and how data structures work internally.

Features
Linked List
Push/pop (front & back)
at(index) with bounds checking
size(), empty(), clear()
Deep copy (copy constructor + assignment)
Extra: find, insert_before, remove_last, remove_every_other
Circular Vector
Push/pop (front & back)
Automatic resizing (capacity doubles)
Circular indexing (wrap-around behavior)
at(index), size(), empty()
Extra: find, insert_before, remove_last, remove_every_other
Testing

Tested using Google Test with coverage for:

Core operations (push/pop, size, access)
Edge cases (empty structures, bounds errors)
Copy/assignment correctness
Advanced operations

LinkedList tests:
CircVector tests:

Build & Run
make list_tests
./list_tests

Key Takeaways
Implemented data structures without STL
Practiced pointer manipulation and memory safety
Learned dynamic resizing and circular indexing
Strengthened debugging using unit tests
Author: Christian Aguirre
