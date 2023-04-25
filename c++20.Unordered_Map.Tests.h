#include <iostream>
#include <unordered_map>
#include <cstdlib>

enum class RouteTarget_EnumClass : int
{
   _lhs,
   _rhs,
   _root
};

int main()
{
    std::unordered_map <
    RouteTarget_EnumClass, 
    std::unordered_map < 
    uint64_t,
    bool >> 
    guid_library; 
    
    guid_library = 
    {
        {RouteTarget_EnumClass::_rhs, 
            {
                {1, true},
                {2, true},
                {3, true},
                {4, true},
                {5, true},
            }
        }
    };
    
    const auto& it = guid_library.find(RouteTarget_EnumClass::_lhs);
    
    if (it == guid_library.end())
    {
        std::cout << "guid_library [ " << "RouteTarget_EnumClass::_lhs ] invalid enumeration key" << std::endl;
        return EXIT_SUCCESS;
    }
    
    std::cout << "guid_library.at(RouteTarget_EnumClass::_rhs" << std::endl;
    
    for(const auto& [idx_uint64, boolType] : guid_library[RouteTarget_EnumClass::_rhs])
    {
        std::cout << "{" << idx_uint64 << ", " << std::boolalpha << boolType << "}, " << std::endl;
    }

    return EXIT_SUCCESS;
}
