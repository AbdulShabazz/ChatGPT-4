#include <iostream>
#include <cstdlib>
#include <vector>

int main()
{
    std::vector<
    uint64_t> u { 0 };
    
    std::vector<
    std::vector<
    uint64_t>> result {};
    
    for (int i = 1 ; i < 11; ++i)
    {
        u[0] = i;
        result.emplace_back (u);
    }
    
    for (const std::vector<uint64_t>& u : result)
    {
        std::cout << u[0] << " ";
    }

    return EXIT_SUCCESS;
}
