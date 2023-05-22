#include <vector>
#include <functional>

template <typename T>
size_t hashVector(const std::vector<T>& vec) {
    std::hash<T> hasher;
    size_t hash = 0;
    for (const auto& elem : vec) {
        // Combine the hash of the current element with the hash so far using XOR and bit shifting
        hash ^= hasher(elem) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
}

/*The hash combination formula used is a good generic combination which is known to work well in many situations. It's borrowed from Boost library.*/
