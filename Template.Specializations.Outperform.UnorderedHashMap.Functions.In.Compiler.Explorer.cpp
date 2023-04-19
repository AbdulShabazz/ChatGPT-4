#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>
#include <functional>
#include <cstdlib>

struct Axiom_Struct
{

};

struct Theorem_Struct
{
  const uint64_t LHSPrimaryKey_UInt64{};
  const uint64_t RHSPrimaryKey_UInt64{};
  const uint64_t TotalProofsFound_UInt64{};
  const uint64_t MaxAllowedProofs_UInt64 = 1;
};

enum class RouteSource_EnumClass:int
{
  _root,
  _lhs,
  _rhs
};

enum class Indirection_EnumClass:int
{
  _auto,
  _lhs,
  _rhs
};

// Template specialization implementation dissasembly: 70 lines
template<RouteSource_EnumClass,Indirection_EnumClass>
void Auto(Theorem_Struct, Axiom_Struct, bool, bool);

template<>
void Auto<RouteSource_EnumClass::_root,Indirection_EnumClass::_auto>(Theorem_Struct, Axiom_Struct, bool TotalProofsFound_, bool MaxAllowedProofs_)
{
  std::cout << "Hello World!" << std::endl;
};

int main ()
{
    Theorem_Struct InTheorem;
    const Axiom_Struct InAxiom;
    
    const bool en = 
    InTheorem.LHSPrimaryKey_UInt64 == InTheorem.RHSPrimaryKey_UInt64;
    Auto<RouteSource_EnumClass::_root,Indirection_EnumClass::_auto>(InTheorem, InAxiom,true,true);
    
    return EXIT_SUCCESS;
}

/*
std::unordered_map <bool, std::unordered_map <bool, std::unordered_map <RouteSource_EnumClass,std::unordered_map <Indirection_EnumClass,std::function<void(Theorem_Struct, Axiom_Struct)>>>>> Axiom;
    Axiom[true][true][RouteSource_EnumClass::_root][Indirection_EnumClass::_auto] = [](Theorem_Struct InTheorem, const Axiom_Struct & InAxiom) -> void
    {
      std::cout << "Hello World!" << std::endl;
    };
    
    const bool en = 
    InTheorem.LHSPrimaryKey_UInt64 == InTheorem.RHSPrimaryKey_UInt64;
    Axiom[en][en][RouteSource_EnumClass::_root][Indirection_EnumClass::_auto](InTheorem, InAxiom);
*/


/*
// Template specialization implementation dissasembly: 70 lines
template<bool,bool,RouteSource_EnumClass,Indirection_EnumClass>
void Auto(Theorem_Struct, Axiom_Struct);

template<>
void Auto<true,true,RouteSource_EnumClass::_root,Indirection_EnumClass::_auto>(Theorem_Struct, Axiom_Struct)
{
  std::cout << "Hello World!" << std::endl;
};

int main ()
{
    Theorem_Struct InTheorem;
    const Axiom_Struct InAxiom;
    
    const bool en = 
    InTheorem.LHSPrimaryKey_UInt64 == InTheorem.RHSPrimaryKey_UInt64;
    Auto<true,true,RouteSource_EnumClass::_root,Indirection_EnumClass::_auto>(InTheorem, InAxiom);
    
    return EXIT_SUCCESS;
}
*/
