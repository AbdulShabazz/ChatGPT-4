
**Title:** Proposal for `std::fiber<T>` Language-Level Extension in C++23

**Document number:** N/A

**Date:** 2023-07-07

**Project:** Programming Language C++

**Reply to:** ahshabazz

**Introduction**

Dear Members of the C++ Standards Committee,

This document proposes a novel language-level extension to the C++ Standard Library, namely `std::fiber<T>`, aimed to ease and optimize concurrent programming by providing automated management of shared state.

## Motivation and Scope

Concurrent programming is a challenging aspect of C++, requiring careful synchronization to avoid data races and associated undefined behavior. This proposal seeks to mitigate these challenges by introducing a unit of execution, `std::fiber<T>`, designed with built-in Read-Copy-Update (RCU) or Copy-On-Write (COW) semantics to handle shared state. This approach simplifies concurrent programming, allowing programmers to reason about each fiber's execution as if it were single-threaded, whilst the complexity of managing shared state is handled by the language or runtime.

## Proposal

Today we propose `std::fiber<T>`, a lightweight unit of execution with its own private data `T`. Each fiber would employ RCU or COW semantics when sharing data with other fibers, minimizing data races while optimizing memory usage and execution speed.

To address the many challenges associated with thread management, we suggest the following solutions:

1. **Performance Overhead**: Apply "lazy copying" and diffing techniques, where data is copied only when it's about to be modified, and only the parts of the data that have changed are copied and updated.

2. **Synchronization**: Use efficient lock-free algorithms, where possible, to manage synchronization, and design flexibility into the API to allow advanced users to apply manual synchronization when necessary.

3. **Garbage Collection**: Implement deterministic memory management, such as reference counting or region-based memory management strategies, or consider employing a simple garbage collector specifically for managing the lifetimes of these shared data structures.

4. **API Design**: Design the `std::fiber<T>` API such that certain variables can be marked as shared, possibly with a keyword or physical annotation. Alternatively, all variables in a fiber could be private by default, with explicit sharing of variables only as required.

5. **Semantic Complexity**: Provide comprehensive documentation, usage examples, and tooling support (like static analysis tools) to assist developers in understanding and effectively using `std::fiber<T>`.

## Impact on the Standard

This proposal does not anticipate any breaking changes to the existing C++ standard, as `std::fiber<T>` would be a new addition that complements the existing concurrency model.

The addition of `std::fiber<T>` would likely involve modifications to the C++ memory model to account for the proposed RCU or COW semantics. Further, to accommodate the garbage collection strategies, modifications may be required in the language's resource management model.

## Future Directions

Following the adoption of `std::fiber<T>`, we suggest exploring these areas of further optimizations, such as fine-tuning the garbage collection strategy, enhancing the lock-free algorithms, or refining the copy strategies. We also recommend developing further tooling support to aid in the effective use of `std::fiber<T>`.

We hope this proposal will be considered for inclusion in the C++23 standard. We look forward to your feedback and are ready to revise and refine this proposal based on the committee's suggestions.

Best Regards,

Abdul S.

**Acknowledgments**

N/A

**References**

N/A

**Revision History**

N/A
