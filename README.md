# Data Structures in C++

Implementation of core data structures built from scratch in C++ with full unit testing.

---

## Overview

This project focuses on building and understanding fundamental data structures without using the STL.  
It includes a Linked List and a Circular Vector, along with tests to verify correctness.

---

## Features

### Linked List
- Insert/remove from front and back  
- Access elements with bounds checking  
- Deep copy (copy constructor + assignment operator)  
- Extra operations: find, insert_before, remove_last, remove_every_other  

### Circular Vector
- Dynamic resizing (capacity doubles when full)  
- Circular indexing (wrap-around behavior)  
- Access elements with bounds checking  
- Extra operations similar to Linked List  

---

## Testing

Tested using Google Test with coverage for:
- Core operations  
- Edge cases and exceptions  
- Copy and assignment correctness  

---

## Build & Run

```bash
make list_tests
./list_tests
