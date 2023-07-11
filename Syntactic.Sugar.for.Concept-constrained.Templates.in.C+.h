Syntactic Sugar for Concept-constrained Templates in C++

---
**Document Number:** NXXXX
**Date:** 2023-07-10
**Project:** Programming Language C++, Evolution Working Group
**Reply to:** [Your Name], [Your Email]

---
# Syntactic Sugar for Concept-constrained Templates in C++

## Introduction

This paper proposes a more intuitive and readable syntax for concept-constrained templates in C++. This approach aims to improve code clarity, making it easier for developers to read and write code involving concepts.

## Motivation and Scope

Concepts, introduced in C++20, have proven to be powerful tools for constraining templates. However, their usage in template declarations can be verbose and somewhat unintuitive for developers new to the feature or the language. There is an opportunity for a syntax sugar to streamline the declaration of concept-constrained templates.

## Impact on the Standard

This is a pure extension and does not modify any existing syntax, thus backward compatibility is not affected.

## Design Decisions

The proposal is to introduce an infix keyword `as` to bind template parameters with their concepts directly in the template declaration. It looks as follows:

```cpp
template <std::builtin::Sortable as T>
void sort(T& collection) {
    std::sort(collection.begin(), collection.end());
}
```

In this proposed syntax, `std::builtin::Sortable as T` denotes that `T` is a type that must satisfy the `Sortable` concept. This syntax offers a clear, single-line declaration of the concept constraint and the template parameter.

## Technical Specifications

The `as` keyword is to be introduced, and its use is confined to template declarations. When used in this context, it binds a template parameter with a concept.

The semantics of the concept check remain unchanged - if a type does not meet the concept requirements, a substitution failure occurs.

## Future Directions

Further improvements could be considered to enhance the syntax and semantics of template concept constraints based on the adoption and user feedback of this proposal.

## Acknowledgements

Thanks to all those who have given feedback and helped shape this proposal.

## References

Stroustrup, B. (2020). A Tour of C++ (2nd Edition). Addison-Wesley.

---
