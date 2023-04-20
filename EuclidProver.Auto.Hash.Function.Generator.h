#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>
#include <functional>
#include <cstdlib>

int main ()
{
    std::array<std::string,2> l2 = { "false", "true" };
    std::array<std::string,3> l3 = { "_root", "_lhs", "_rhs" };
    std::array<std::string,3> l4 = { "_auto", "_reduce", "_expand" };
        
    const std::string buff = " \
    InTheorem.ProofStack_VecUInt64.push_back(InAxiom); \n\
    \n\
    if(InTheorem.LHSPrimaryKey_UInt64 == InTheorem.RHSPrimaryKey_UInt64)\n\
    {\n\
        InTheorem.ProofFound_Flag = true;\n\
      ++InTheorem.TotalProofsFound_UInt64;\n\
    }\n\
    \n\
    if(InTheorem.TotalProofsFound_UInt64 >= InTheorem.MaxAllowedProofs_UInt64)\n\
      return;\n\
\n\
    Theorem_Struct TheoremProto_0000 = InTheorem;\n\
    Theorem_Struct TheoremProto_0001 = InTheorem;\n\
    Theorem_Struct TheoremProto_0002 = InTheorem;\n\
    Theorem_Struct TheoremProto_0003 = InTheorem;\n\
    Theorem_Struct TheoremProto_0004 = InTheorem;\n\
    Theorem_Struct TheoremProto_0005 = InTheorem;\n\
    \n\
    if(TheoremProto_0000.SubnetFound_LHS(InAxiom.LHSPrimaryKey_UInt64))\n\
        TheoremProto_0000.UpdatePrimaryKey_LHS(InAxiom.LHSPrimaryKey_UInt64);\n\
        \n\
    TheoremProto_0001.UpdatePrimaryKey_RHS(InAxiom.LHSPrimaryKey_UInt64);\n\
    TheoremProto_0002.UpdatePrimaryKey_LHS(InAxiom.LHSPrimaryKey_UInt64);\n\
    TheoremProto_0002.UpdatePrimaryKey_RHS(InAxiom.RHSPrimaryKey_UInt64);\n\
    \n\
    TheoremProto_0003.UpdatePrimaryKey_LHS(InAxiom.RHSPrimaryKey_UInt64);\n\
    TheoremProto_0004.UpdatePrimaryKey_RHS(InAxiom.RHSPrimaryKey_UInt64);\n\
    TheoremProto_0005.UpdatePrimaryKey_LHS(InAxiom.RHSPrimaryKey_UInt64);\n\
    TheoremProto_0005.UpdatePrimaryKey_RHS(InAxiom.LHSPrimaryKey_UInt64);\n\
    \n\
    std::for_each(std::execution::par_unseq,\n\
        Axioms_Vec.begin(),\n\
        Axioms_Vec.end(),\n\
        [&](const Axiom_Struct& Axiom)\n\
        {\n\
            RecursionLimiter::Invoke limiter(6);\n\
            if (limiter.acquired())\n\
            {\n\
                Auto\n\
                [TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0000.TotalProofsFound_UInt64 >= TheoremProto_0000.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0000, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0000.TotalProofsFound_UInt64 >= TheoremProto_0000.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0000, Axiom);\n\
                \n\
                Auto\n\
                [TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0001.TotalProofsFound_UInt64 >= TheoremProto_0001.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0001, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0001.TotalProofsFound_UInt64 >= TheoremProto_0001.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0001, Axiom);\n\
                \n\
                Auto\n\
                [TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0002.TotalProofsFound_UInt64 >= TheoremProto_0002.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0002, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0002.TotalProofsFound_UInt64 >= TheoremProto_0002.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0002, Axiom);\n\
    \n\
                limiter.release();\n\
            }\n\
    \n\
        });\n\
    \n\
    std::for_each(std::execution::par_unseq,\n\
        Axioms_Vec.begin(),\n\
        Axioms_Vec.end(),\n\
        [&](const Axiom_Struct& Axiom)\n\
        {\n\
            RecursionLimiter::Invoke limiter(6);\n\
            if (limiter.acquired())\n\
            {\n\
                Auto\n\
                [TheoremProto_0003.LHSPrimaryKey_UInt64 == TheoremProto_0003.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0003.TotalProofsFound_UInt64 >= TheoremProto_0003.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0003, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0003.LHSPrimaryKey_UInt64 == TheoremProto_0003.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0003.TotalProofsFound_UInt64 >= TheoremProto_0003.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0003, Axiom);\n\
                \n\
                Auto\n\
                [TheoremProto_0004.LHSPrimaryKey_UInt64 == TheoremProto_0004.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0004.TotalProofsFound_UInt64 >= TheoremProto_0004.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0004, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0004.LHSPrimaryKey_UInt64 == TheoremProto_0004.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0004.TotalProofsFound_UInt64 >= TheoremProto_0004.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0004, Axiom);\n\
                \n\
                Auto\n\
                [TheoremProto_0005.LHSPrimaryKey_UInt64 == TheoremProto_0005.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0005.TotalProofsFound_UInt64 >= TheoremProto_0005.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0005, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0005.LHSPrimaryKey_UInt64 == TheoremProto_0005.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0005.TotalProofsFound_UInt64 >= TheoremProto_0005.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0005, Axiom);\n\
    \n\
                limiter.release();\n\
            }\n\
    \n\
        });\n\
    \n\
    std::for_each(std::execution::par_unseq,\n\
        Axioms_Vec.begin(),\n\
        Axioms_Vec.end(),\n\
        [&](const Axiom_Struct& Axiom)\n\
        {\n\
            RecursionLimiter::Invoke limiter(12);\n\
            if (limiter.acquired())\n\
            {\n\
                Auto\n\
                [TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0000.TotalProofsFound_UInt64 >= TheoremProto_0000.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0000, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0000.TotalProofsFound_UInt64 >= TheoremProto_0000.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0000, Axiom);\n\
                \n\
                Auto\n\
                [TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0001.TotalProofsFound_UInt64 >= TheoremProto_0001.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0001, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0001.TotalProofsFound_UInt64 >= TheoremProto_0001.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0001, Axiom);\n\
                \n\
                Auto\n\
                [TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0002.TotalProofsFound_UInt64 >= TheoremProto_0002.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0002, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0002.TotalProofsFound_UInt64 >= TheoremProto_0002.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0002, Axiom);\n\
                \n\
                \n\
                Auto\n\
                [TheoremProto_0003.LHSPrimaryKey_UInt64 == TheoremProto_0003.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0003.TotalProofsFound_UInt64 >= TheoremProto_0003.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0003, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0003.LHSPrimaryKey_UInt64 == TheoremProto_0003.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0003.TotalProofsFound_UInt64 >= TheoremProto_0003.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0003, Axiom);\n\
                \n\
                Auto\n\
                [TheoremProto_0004.LHSPrimaryKey_UInt64 == TheoremProto_0004.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0004.TotalProofsFound_UInt64 >= TheoremProto_0004.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0004, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0004.LHSPrimaryKey_UInt64 == TheoremProto_0004.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0004.TotalProofsFound_UInt64 >= TheoremProto_0004.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0004, Axiom);\n\
                \n\
                Auto\n\
                [TheoremProto_0005.LHSPrimaryKey_UInt64 == TheoremProto_0005.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0005.TotalProofsFound_UInt64 >= TheoremProto_0005.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_lhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0005, Axiom);\n\
    \n\
                Auto\n\
                [TheoremProto_0005.LHSPrimaryKey_UInt64 == TheoremProto_0005.RHSPrimaryKey_UInt64]\n\
                [TheoremProto_0005.TotalProofsFound_UInt64 >= TheoremProto_0005.MaxAllowedProofs_UInt64]\n\
                [RouteSource_EnumClass::_rhs]\n\
                [Indirection_EnumClass::_reduce]\n\
                (TheoremProto_0005, Axiom);\n\
    \n\
                limiter.release();\n\
            }\n\
    \n\
        });\n";
    
    for(const std::string& ProofFound_Str : l2)
    {
        for(const std::string& TotalProofsFound_Str : l2)
        {
            for(const std::string& RouteSource_Str : l3)
            {
                for(const std::string& Indirection_Str : l4)
                {
                    std::cout << "Axiom\n[" << ProofFound_Str << "]\n[" << TotalProofsFound_Str << "]\n[" << "RouteSource_EnumClass::" << RouteSource_Str << "]\n[Indirection_EnumClass::" << Indirection_Str << "] = \n[](Theorem_Struct InTheorem, const Axiom_Struct & InAxiom) -> void\n{\n" << buff << "\n};\n" << std::endl;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
