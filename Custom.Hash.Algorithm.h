#include <iostream>
#include <cstdint>
#include <functional>
#include <chrono>
#include <unordered_map>

void profiler (std::function<void()> f)
{
    auto start_time_chrono = std::chrono::high_resolution_clock::now ();
    
    f();
    
    std::cout << std::endl;
    auto end_time_chrono = std::chrono::high_resolution_clock::now();
    auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>( end_time_chrono - start_time_chrono ).count();
    std::cout << "Total Duration (nanoseconds): " << duration_chrono << "\n\n";
}

struct HASHER {
    template<typename T = std::string>
    std::size_t operator()(const T& key) const {
        std::size_t hash = 0;
        for (const char& c : key) {
            hash = hash * 101 + int{c}; // Duration (nanoseconds): 5372763216 vs 3570603510 (Default)
            
          //hash ^= hash *int{c} + 0x9e3779b9 + (hash << 6) + (hash >> 2); // Duration (nanoseconds): inf vs 3570603510 (Default)
        }
        return hash;
    }
};

int main ()
{
    std::unordered_multimap<std::string, int> hmap_default;
    std::unordered_multimap<std::string, int, HASHER> hmap_custom;
    
    profiler([&]()
    {
        for(int i = 0; i < 5000'000; ++i)
        {
            hmap_default.emplace(std::string{i},i);
        }
        for(int i = 0; i < 5000'000; ++i)
        {
            hmap_default.find(std::string{i});
        }
        std::cout << "Default implementation: 500\'000 insertions.";
    });
    
    profiler([&]()
    {
        for(int i = 0; i < 5000'000; ++i)
        {
            hmap_custom.emplace(std::string{i},i);
        }
        for(int i = 0; i < 5000'000; ++i)
        {
            hmap_custom.find(std::string{i});
        }
        std::cout << "Custom implementation: 500\'000 insertions.";
    });
    
    return EXIT_SUCCESS;
}

/*
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

*/
/*The hash combination formula used is a good generic combination which is known to work well in many situations. It's borrowed from Boost library.*/
