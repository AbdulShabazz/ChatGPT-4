Title: Proposal to add constexpr_hash Functionality to the C++ Standard Library

**Document Number**: Nxxxx

**Date**: 17-JULY-2023-1502 H

**Revises**: N/A

**Reply to**: ahshabazz

1. Introduction:

This document proposes the addition of a compile-time constexpr hash function to the C++ standard library as a new language level extension. This function, tentatively named constexpr_hash, aims to provide a mechanism for hashing literal strings at compile-time, producing a unique identifier for each distinct string that can be used as a key in resource mapping, among many other use-cases.

2. Rationale:

While C++ currently offers a run-time std::hash function, no standard library feature is available for hashing at compile-time. This feature would benefit various applications, including but not limited to:

  - Resource mapping in embedded systems, where runtime overhead is a crucial consideration.
  - Obfuscation purposes, where the identifiers of strings would be obfuscated in the compiled binary.
  - Performance optimizations in cases where the compile-time calculation of hashes would be beneficial.

One possible implementation of the constexpr_hash function is as follows:

```
constexpr uint32_t constexpr_hash(const char* str, uint32_t value = 0, uint32_t seed = 1000003) {
    return (str[0] == '\0') ? value : seed * constexpr_hash(str + 1, seed) ^ static_cast<uint32_t>(str[0]);
}

struct Resource {
    const uint32_t key;
    const char* value;
};

constexpr Resource resources[] = {
    { constexpr_hash("Hello"), "Hello" },
    { constexpr_hash("World"), "World" },
    // Add more strings here...
};

// Check for collisions
constexpr bool has_collision() {
    for (int i = 0; i < sizeof(resources)/sizeof(resources[0]); i++) {
        for (int j = i+1; j < sizeof(resources)/sizeof(resources[0]); j++) {
            if (resources[i].key == resources[j].key) {
                return true;
            }
        }
    }
    return false;
}

static_assert(!has_collision(), "Hash collision detected. Please change the hash function seed.");

const char* get_resource(uint32_t key) {
    for (const auto& resource : resources) {
        if (resource.key == key) {
            return resource.value;
        }
    }

    // Handle missing key //
    return nullptr;
}

int main() {
    auto key = constexpr_hash("Hello");
    auto value = get_resource(key);
    std::cout << "Key: " << key << ", Value: " << value << std::endl;
    return 0;
}
```

3. Proposal:

We propose the following signature for the constexpr_hash function:

```
constexpr std::size_t constexpr_hash(const char* str, std::size_t value = 0, std::size_t seed = <default_seed_value>);
```

The function accepts a null-terminated string, an optional initial hash value, and an optional seed value. The seed can be adjusted (preferably at compile time) to mitigate the potential for collisions. The function returns the hash value of the string.

The exact implementation of the hash function is subject to further discussion. The hash function should balance the needs for performance, collision resistance, and simplicity.

4. Example Usage:

Here is an example of how the constexpr_hash function might be used:

```
constexpr auto key = constexpr_hash("Hello, World!");
std::unordered_map<std::size_t, std::string> map;
map[key] = "Hello, World!";

// Usage //
std::cout << map[key] << std::endl;
```

5. Impact on the Standard:

The proposed feature would not introduce any breaking changes. The constexpr_hash function could be added to the <functional> header alongside std::hash.

6. Compatibility:

The proposed feature does not conflict with any existing features. It simply provides an additional tool for C++ developers to use at their discretion.

7. Implementation:

Implementing the constexpr_hash function would not require any changes to the core language or compiler infrastructure. It could be implemented purely as a library extension.

8. Conclusion:

The addition of a constexpr_hash function to the C++ standard library would provide a useful tool for developers working on resource-constrained systems, obfuscation, and certain performance optimizations. We urge the committee to consider this proposal for inclusion in a future version of the C++ standard.
