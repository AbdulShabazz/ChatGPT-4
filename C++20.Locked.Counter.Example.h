#include <iostream>
#include <cstdlib>

template <typename T>
class Counter
{
public:
    explicit Counter(const uint64_t& max) : max_{max}
    {
        
    }
    
    uint64_t operator() ()
    {
        const uint64_t n = num;
        if (num < max_)
        {
            ++num;
        }
        return n;
    }
    
private:
    const uint64_t max_ {};
    uint64_t num {};
};

int main()
{
    Counter<uint64_t> counter {10};
    
    for (uint64_t i = 0; i < 20; ++i)
    {
        std::cout << "num: " << counter() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
