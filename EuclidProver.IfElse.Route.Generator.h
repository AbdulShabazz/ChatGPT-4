#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

using namespace std;

int main()
{
    std::vector<std::string> _1 = { "All", "LHS", "RHS" };
    std::vector<std::string> _2 = { "LHS", "RHS" };
    
    for(const std::string& s1 : _1)
    {
        for(const std::string& s2 : _1)
        {
            std::cout << "const bool Call" << s1 << "Route" << s2 << "_Flag =" << std::endl;
        }
    }
    
    for(const std::string& s2 : _1)
    {
        for(const std::string& s4 : _1)
        {
            std::cout << "const bool CallLHSRoute" << s2 << "_CallRHSRoute" << s4 << "_Flag =" << std::endl;
        }
    }
    
    cout<<"Hello World";

    return EXIT_SUCCESS;
}
