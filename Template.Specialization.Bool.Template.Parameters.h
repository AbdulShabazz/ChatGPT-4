/*
Q:How can I make this code compile?

A:The issue in your code is that you're trying to use non-constexpr values as template parameters, specifically ProofFound_TemplateParameterFlag and TotalProofsFoundGEMaxAllowedProofs_TemplateParameterFlag. Template parameters must be known at compile-time, so you need to modify the code accordingly.

One possible solution is to use if constexpr and call the appropriate specialization of the Auto function based on the conditions. Here's a modified version of your code that should compile:

cpp
*/
#include <iostream>
#include <cstdint>

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

enum class RouteSource_EnumClass : int
{
    _root,
    _lhs,
    _rhs
};

enum class Indirection_EnumClass : int
{
    _auto,
    _reduce,
    _expand
};

template <RouteSource_EnumClass R, Indirection_EnumClass I>
void Auto(Theorem_Struct InTheorem, const Axiom_Struct& InAxiom, bool ProofFound, bool TotalProofsFoundGEMaxAllowedProofs)
{
    if constexpr (R == RouteSource_EnumClass::_root && I == Indirection_EnumClass::_auto)
    {
        if (!ProofFound && !TotalProofsFoundGEMaxAllowedProofs)
        {
            std::cout << "Hello World!" << std::endl;
        }
    }
}

int main()
{
    Theorem_Struct InTheorem;
    const Axiom_Struct Axiom;

    const bool ProofFound_TemplateParameterFlag =
        InTheorem.LHSPrimaryKey_UInt64 ==
        InTheorem.RHSPrimaryKey_UInt64;
    const bool TotalProofsFoundGEMaxAllowedProofs_TemplateParameterFlag =
        InTheorem.TotalProofsFound_UInt64 >=
        InTheorem.MaxAllowedProofs_UInt64;

    Auto<RouteSource_EnumClass::_root, Indirection_EnumClass::_auto>(InTheorem, Axiom, ProofFound_TemplateParameterFlag, TotalProofsFoundGEMaxAllowedProofs_TemplateParameterFlag);
    return EXIT_SUCCESS;
}
/*
In this version, I removed the template parameters ProofFound_TemplateParameterFlag and TotalProofsFoundGEMaxAllowedProofs_TemplateParameterFlag from the Auto function, and instead added them as regular function arguments. I then used if constexpr inside the function to call the appropriate specialization based on the conditions. This allows the code to compile and run correctly.

SFINAE

Specification Failed Initialization Is Not An Error
*/
