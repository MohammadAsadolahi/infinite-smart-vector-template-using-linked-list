<p align="center">
  <img src="https://img.shields.io/badge/C++-11%2F14-blue?style=for-the-badge&logo=cplusplus&logoColor=white" />
  <img src="https://img.shields.io/badge/Data%20Structure-Linked%20List-brightgreen?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Memory-Smart%20Pointers-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" />
</p>

# SmartVector\<T\>

**A memory-safe, dynamically-sized, template-based vector built on a linked list backbone — leveraging modern C++ smart pointers to eliminate manual memory management entirely.**

---

## The Problem

Traditional C++ containers force a choice: use `std::vector` with contiguous memory and costly reallocations, or use `std::list` and sacrifice random access. Raw pointers in either case open the door to memory leaks, dangling references, and undefined behavior — the class of bugs responsible for [~70% of security vulnerabilities](https://www.chromium.org/Home/chromium-security/memory-safety/) in large C++ codebases.

## The Solution

`SmartVector<T>` bridges the gap — a **generic, infinitely-growable container** that:

- Provides **array-style subscript access** (`operator[]`) over a linked list
- Uses `std::shared_ptr` exclusively — **zero raw pointers, zero manual `delete`**
- Supports **any data type** via C++ templates
- Throws **descriptive, heap-allocated exceptions** for bounds violations
- Maintains an internal element count for O(1) size queries

---

## Architecture

```
SmartVector<T>
│
├── root ──→ [Node] ──→ [Node] ──→ [Node] ──→ nullptr
│             │           │           │
│         shared_ptr   shared_ptr   shared_ptr
│           <T>          <T>          <T>
│
├── count: int
│
└── Template Parameter: T (any copyable type)
```

| Component | Type | Purpose |
|-----------|------|---------|
| `Node` | Private inner class | Encapsulates element data + next-pointer |
| `Node::data` | `shared_ptr<T>` | Heap-allocated, reference-counted element storage |
| `Node::nextNode` | `shared_ptr<Node>` | Automatic lifetime management of list linkage |
| `root` | `shared_ptr<Node>` | Head of the linked list |
| `count` | `int` | O(1) element count |

---

## API Reference

```cpp
SmartVector<int> vec;
```

| Method | Signature | Complexity | Description |
|--------|-----------|------------|-------------|
| **add** | `add(T data) → void` | O(n) | Appends an element to the end of the vector |
| **remove** | `remove(int index) → void` | O(n) | Removes the element at the given index |
| **getCount** | `getCount() → int` | O(1) | Returns the current number of elements |
| **operator[]** | `operator[](int index) → T&` | O(n) | Random access by index — returns a mutable reference |

All mutating operations throw `unique_ptr<Exception>` on bounds violations with human-readable descriptions.

---

## Usage

```cpp
#include "SmartVector.cpp"

int main() {
    SmartVector<int> numbers;

    // Build the collection
    numbers.add(23);
    numbers.add(24);
    numbers.add(25);
    numbers.add(26);

    // Query
    std::cout << "Count: " << numbers.getCount() << std::endl;  // 4
    std::cout << "Element at [1]: " << numbers[1] << std::endl;  // 24

    // Mutate in-place via subscript
    numbers[0] = 28;

    // Remove by index
    numbers.remove(1);

    std::cout << "Count: " << numbers.getCount() << std::endl;  // 3
}
```

### Exception Handling

```cpp
try {
    numbers[999] = 42;  // out of bounds
} catch (unique_ptr<Exception>& e) {
    (*e) << cout;  // "can't access object, index out of vector"
}
```

---

## Design Decisions

| Decision | Rationale |
|----------|-----------|
| **`shared_ptr` over `unique_ptr` for nodes** | Simplifies traversal and copy semantics — nodes can be safely referenced from multiple traversal pointers without ownership ambiguity |
| **Linked list over contiguous array** | Eliminates reallocation overhead — the vector grows node-by-node with no capacity doubling or element copying |
| **Heap-allocated exceptions** | Exceptions carry descriptive payloads via `unique_ptr<Exception>`, enabling rich error context without slicing |
| **Trailing return type syntax** | Consistent use of `auto f() -> ReturnType` aligns with modern C++ style |
| **Template in `.cpp`** | Implementation kept in `.cpp` with direct `#include` from `Main.cpp` — a deliberate choice for source organization |

---

## Complexity Analysis

| Operation | Time | Space |
|-----------|------|-------|
| `add` | O(n) | O(1) per call |
| `remove` | O(n) | O(1) |
| `operator[]` | O(n) | O(1) |
| `getCount` | O(1) | O(1) |
| Destruction | O(n) | O(1) — handled automatically by `shared_ptr` ref-count cascade |

---

## Build & Run

```bash
# GCC
g++ -std=c++14 -o smartvector Main.cpp

# Clang
clang++ -std=c++14 -o smartvector Main.cpp

# Run
./smartvector
```

---

## Project Structure

```
.
├── SmartVector.h      # Class declaration, Node definition, Exception class
├── SmartVector.cpp    # Template method implementations
├── Main.cpp           # Driver / usage demonstration
└── README.md
```

---

## Future Directions

- [ ] Iterator support (`begin()` / `end()`) for range-based `for` loops
- [ ] `insert(int index, T data)` for positional insertion
- [ ] Move semantics support (`T&&`) for zero-copy element addition
- [ ] `tail` pointer for O(1) append
- [ ] Allocator-aware variant for custom memory strategies

---

<p align="center">
  <sub>Built with modern C++ principles — because memory safety isn't optional, it's foundational.</sub>
</p>
