#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>
#include <functional>
#include <cstdlib>

int main ()
{
    std::array<std::string,3> l3 = { "_root", "_lhs", "_rhs" };
    std::array<std::string,3> l4 = { "_auto", "_reduce", "_expand" };
    
    for(int k = 0; k < 3; k++)
    {
        for(int m = 0; m < 3; m++)
        {
            std::cout << "template <>	// Template specialization of the primary template function" << std::endl;
            std::cout << "__forceinline void Auto <" << std::endl;
            std::cout << "RouteSource_EnumClass :: " << l3[k] << "," << std::endl;
            std::cout << "Indirection_EnumClass :: " << l4[m] << " > (" << std::endl;
            std::cout << "\tTheorem_Struct InTheorem," << std::endl;
            std::cout << "\tconst Axiom_Struct& InAxiom," << std::endl;
            std::cout << "\tconst bool& InProofFound_ParameterFlag," << std::endl;
            std::cout << "\tconst bool& InTotalProofsGEMaxAllowedProofs_ParameterFlag)" << std::endl;
            std::cout << "{\n" << std::endl;
            std::cout << "\
	Theorem_Struct TheoremProto_0000 = InTheorem; \n\
	Theorem_Struct TheoremProto_0001 = InTheorem; \n\
	Theorem_Struct TheoremProto_0002 = InTheorem; \n\
	Theorem_Struct TheoremProto_0003 = InTheorem; \n\
	Theorem_Struct TheoremProto_0004 = InTheorem; \n\
	Theorem_Struct TheoremProto_0005 = InTheorem; \n\
        \n\
    switch (InTheorem.Indir_EnumClass) \n\
	{ \n\
		case Indirection_EnumClass::_reduce: \n\
			std::for_each(std::execution::par_unseq, \n\
    			Axioms_Vec.begin(), \n\
    			Axioms_Vec.end(), \n\
    			[&](const Axiom_Struct& Axiom) \n\
    			{ \n\
                    RecursionLimiter::Invoke limiter(6); \n\
                    if (limiter.acquired()) \n\
        			{	\n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0000, Axiom, \n\
        				        TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0000.TotalProofsFound_UInt64 >= TheoremProto_0000.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0000, Axiom, \n\
        				        TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0000.TotalProofsFound_UInt64 >= TheoremProto_0000.MaxAllowedProofs_UInt64); \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0001, Axiom, \n\
        				        TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0001.TotalProofsFound_UInt64 >= TheoremProto_0001.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0001, Axiom, \n\
        				        TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0001.TotalProofsFound_UInt64 >= TheoremProto_0001.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0002, Axiom, \n\
        				        TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0002.TotalProofsFound_UInt64 >= TheoremProto_0002.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0002, Axiom, \n\
        				        TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0002.TotalProofsFound_UInt64 >= TheoremProto_0002.MaxAllowedProofs_UInt64); \n\
        				\n\
        				limiter.release(); \n\
        			} \n\
        			\n\
    			}); \n\
    		break; \n\
        \n\
		case Indirection_EnumClass::_expand: \n\
			std::for_each(std::execution::par_unseq, \n\
    			Axioms_Vec.begin(), \n\
    			Axioms_Vec.end(), \n\
    			[&](const Axiom_Struct& Axiom) \n\
    			{ \n\
                    RecursionLimiter::Invoke limiter(6); \n\
                    if (limiter.acquired()) \n\
        			{	\n\	
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0003, Axiom, \n\
        				        TheoremProto_0003.LHSPrimaryKey_UInt64 == TheoremProto_0003.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0003.TotalProofsFound_UInt64 >= TheoremProto_0003.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0003, Axiom, \n\
        				        TheoremProto_0003.LHSPrimaryKey_UInt64 == TheoremProto_0003.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0003.TotalProofsFound_UInt64 >= TheoremProto_0003.MaxAllowedProofs_UInt64); \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0004, Axiom, \n\
        				        TheoremProto_0004.LHSPrimaryKey_UInt64 == TheoremProto_0004.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0004.TotalProofsFound_UInt64 >= TheoremProto_0004.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0004, Axiom, \n\
        				        TheoremProto_0004.LHSPrimaryKey_UInt64 == TheoremProto_0004.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0004.TotalProofsFound_UInt64 >= TheoremProto_0004.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0005, Axiom, \n\
        				        TheoremProto_0005.LHSPrimaryKey_UInt64 == TheoremProto_0005.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0005.TotalProofsFound_UInt64 >= TheoremProto_0005.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0005, Axiom, \n\
        				        TheoremProto_0005.LHSPrimaryKey_UInt64 == TheoremProto_0005.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0005.TotalProofsFound_UInt64 >= TheoremProto_0005.MaxAllowedProofs_UInt64); \n\
        				\n\
        				limiter.release(); \n\
        			} \n\
    				\n\
    			}); \n\
			break; \n\
        \n\
		case Indirection_EnumClass::_auto: \n\
		default: \n\
			std::for_each(std::execution::par_unseq, \n\
    			Axioms_Vec.begin(), \n\
    			Axioms_Vec.end(), \n\
    			[&](const Axiom_Struct& Axiom) \n\
    			{ \n\	
                    RecursionLimiter::Invoke limiter(12); \n\
                    if (limiter.acquired()) \n\
        			{	\n\	
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0000, Axiom, \n\
        				        TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0000.TotalProofsFound_UInt64 >= TheoremProto_0000.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0000, Axiom, \n\
        				        TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0000.TotalProofsFound_UInt64 >= TheoremProto_0000.MaxAllowedProofs_UInt64); \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0001, Axiom, \n\
        				        TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0001.TotalProofsFound_UInt64 >= TheoremProto_0001.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0001, Axiom, \n\
        				        TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0001.TotalProofsFound_UInt64 >= TheoremProto_0001.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0002, Axiom, \n\
        				        TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0002.TotalProofsFound_UInt64 >= TheoremProto_0002.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _reduce >( \n\
        				        TheoremProto_0002, Axiom, \n\
        				        TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0002.TotalProofsFound_UInt64 >= TheoremProto_0002.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				\n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0003, Axiom, \n\
        				        TheoremProto_0003.LHSPrimaryKey_UInt64 == TheoremProto_0003.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0003.TotalProofsFound_UInt64 >= TheoremProto_0003.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0003, Axiom, \n\
        				        TheoremProto_0003.LHSPrimaryKey_UInt64 == TheoremProto_0003.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0003.TotalProofsFound_UInt64 >= TheoremProto_0003.MaxAllowedProofs_UInt64); \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0004, Axiom, \n\
        				        TheoremProto_0004.LHSPrimaryKey_UInt64 == TheoremProto_0004.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0004.TotalProofsFound_UInt64 >= TheoremProto_0004.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0004, Axiom, \n\
        				        TheoremProto_0004.LHSPrimaryKey_UInt64 == TheoremProto_0004.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0004.TotalProofsFound_UInt64 >= TheoremProto_0004.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _lhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0005, Axiom, \n\
        				        TheoremProto_0005.LHSPrimaryKey_UInt64 == TheoremProto_0005.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0005.TotalProofsFound_UInt64 >= TheoremProto_0005.MaxAllowedProofs_UInt64); \n\
        				    \n\
        				Auto< \n\
        				    RouteSource_EnumClass :: _rhs, \n\
        				    Indirection_EnumClass :: _expand >( \n\
        				        TheoremProto_0005, Axiom, \n\
        				        TheoremProto_0005.LHSPrimaryKey_UInt64 == TheoremProto_0005.RHSPrimaryKey_UInt64, \n\
        				        TheoremProto_0005.TotalProofsFound_UInt64 >= TheoremProto_0005.MaxAllowedProofs_UInt64); \n\
        				\n\
        				limiter.release(); \n\
        			} \n\
    			    \n\
    			}); \n\
			break; \n\
	}\n";
            std::cout << "}\n" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
