#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main()
{
    std::vector<int> v{ 0, 1, 2, 3, 4};
    const int I = v.size();
    for ( int i = 0 ; i < I; ++i)
    {
        v.insert(v.begin() + 1, 1, 1);
    }
    for (const auto& val : v)
    {
        std::cout << val << " " ;
    }

    return 0;
}
