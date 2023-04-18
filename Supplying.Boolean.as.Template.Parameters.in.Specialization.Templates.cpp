/*
Q:How can I supply the bool parameters as a template parameter to a template specialization function?

A:To supply the boolean parameters as template parameters, you can use a helper function that is called recursively to cover all possible combinations of the boolean parameters. This will allow you to create template specializations for each combination of the boolean parameters. Here's an example of how to achieve this:

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

template <
    bool ProofFound_TemplateParameterFlag,
    bool TotalProofsFoundGEMaxAllowedProofs_TemplateParameterFlag,
    RouteSource_EnumClass R,
    Indirection_EnumClass I>
void Auto(Theorem_Struct InTheorem, const Axiom_Struct& InAxiom)
{
    // Default implementation (empty)
}

template <>
void Auto<
    false,
    false,
    RouteSource_EnumClass::_root,
    Indirection_EnumClass::_auto>(
    Theorem_Struct InTheorem,
    const Axiom_Struct& InAxiom)
{
    std::cout << "Hello World!" << std::endl;
}

template <bool B, typename Func>
void static_if(Func&& f)
{
    if constexpr (B)
    {
        f();
    }
}

template <typename Func>
void handle_combinations(bool b1, bool b2, Func&& f)
{
    static_if<true>([&] {
        static_if<true>([&] { f(b1, b2); });
        static_if<false>([&] { f(b1, !b2); });
    });

    static_if<false>([&] {
        static_if<true>([&] { f(!b1, b2); });
        static_if<false>([&] { f(!b1, !b2); });
    });
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

    handle_combinations(
        ProofFound_TemplateParameterFlag,
        TotalProofsFoundGEMaxAllowedProofs_TemplateParameterFlag,
        [&](bool b1, bool b2) {
            Auto<b1, b2, RouteSource_EnumClass::_root, Indirection_EnumClass::_auto>(InTheorem, Axiom);
        });

    return EXIT_SUCCESS;
}

/*
In this example, I created a helper function handle_combinations that takes two boolean values and a lambda function. It calls the lambda function with all possible combinations of the boolean values. The static_if function is a helper function used to enable or disable certain branches based on the compile-time boolean value.

In the main function, I called handle_combinations with the boolean flags, and it calls the appropriate template specialization of the Auto function based on the combination of the boolean values. This approach allows you to supply the boolean parameters as template parameters to a template specialization function.
*/
