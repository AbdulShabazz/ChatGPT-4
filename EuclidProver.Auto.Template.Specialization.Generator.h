#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>
#include <functional>
#include <cstdlib>

int main ()
{
    std::array<std::string,2> l1 = { "false", "true" };
    std::array<std::string,2> l2 = { "false", "true" };
    std::array<std::string,3> l3 = { "_root", "_lhs", "_rhs" };
    std::array<std::string,3> l4 = { "_auto", "_reduce", "_expand" };
    
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                for(int m = 0; m < 3; m++)
                {
                    std::cout << "__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function" << std::endl;
                    std::cout << "void Auto <" << std::endl;
                    std::cout << l1[i] << "," << std::endl;
                    std::cout << l2[j] << "," << std::endl;
                    std::cout << "RouteSource_EnumClass :: " << l3[k] << "," << std::endl;
                    std::cout << "Indirection_EnumClass :: " << l4[m] << " > (" << std::endl;
                    std::cout << "\tTheorem_Struct InTheorem," << std::endl;
                    std::cout << "\tconst Axiom_Struct & InAxiom)" << std::endl;
                    std::cout << "{\n" << std::endl;
                    std::cout << "}\n" << std::endl;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

/*
template < 
bool ProofFound_ParameterFlag,
bool MaxAllowedProofsFound_ParameterFlag,
RouteSource_EnumClass R, 
Indirection_EnumClass B > // Declaration of the primary template function
void Auto ();

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
false,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
false,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
false,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
false,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
false,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
false,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
false,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
false,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
false,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
true,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
true,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
true,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
true,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
true,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
true,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
true,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
true,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
true,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
false,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
false,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
false,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
false,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
false,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
false,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
false,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
false,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
false,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
true,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
true,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
true,
RouteSource_EnumClass :: _root,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
true,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
true,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
true,
RouteSource_EnumClass :: _lhs,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
true,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _auto > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
true,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _reduce > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
true,
true,
RouteSource_EnumClass :: _rhs,
Indirection_EnumClass :: _expand > (
	Theorem_Struct InTheorem,
	const Axiom_Struct & InAxiom)
{

}

/*
__attribute__ ((always_inline)) template <>	// Template specialization of the primary template function
void Auto <
false,
false,
RouteSource_EnumClass :: _auto,
Indirection_EnumClass :: _expand > (
    Theorem_Struct InTheorem,
    const Axiom_Struct & InAxiom)
{
	if (InTheorem.RHSReduceCallGraph_UInt64Map.count(InAxiom.guid) == 0) return;

	if (InTheorem.RHSReduceCallHistory_UInt64Map.count(InAxiom.guid) > 0) return;

	InTheorem.RHSReduceCallHistory_UInt64Map.insert(InAxiom.guid);

	Theorem_Struct TheoremProto_0000 = InTheorem;
	Theorem_Struct TheoremProto_0001 = InTheorem;
	Theorem_Struct TheoremProto_0002 = InTheorem;

	TheoremProto_0000.UpdatePrimaryKey_LHS(InAxiom.RHSPrimaryKey_UInt64, InAxiom.LHSPrimaryKey_UInt64);

	TheoremProto_0001.UpdatePrimaryKey_RHS(InAxiom.RHSPrimaryKey_UInt64, InAxiom.LHSPrimaryKey_UInt64);

	TheoremProto_0002.UpdatePrimaryKey_LHS(InAxiom.RHSPrimaryKey_UInt64, InAxiom.LHSPrimaryKey_UInt64);
	TheoremProto_0002.UpdatePrimaryKey_RHS(InAxiom.RHSPrimaryKey_UInt64, InAxiom.LHSPrimaryKey_UInt64);

	TheoremProto_0000.ProofStack_VecUInt64.push_back(InAxiom.guid);
	TheoremProto_0001.ProofStack_VecUInt64.push_back(InAxiom.guid);
	TheoremProto_0002.ProofStack_VecUInt64.push_back(InAxiom.guid);

	if (TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64)
	{
		TotalProofsFound_UInt64++;
		ProofFound_Flag = true;
		if (TotalProofsFound_UInt64 >= MaxAllowedProofs_UInt64) return;
	}

	if (TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64)
	{
		TotalProofsFound_UInt64++;
		ProofFound_Flag = true;
		if (TotalProofsFound_UInt64 >= MaxAllowedProofs_UInt64) return;
	}

	if (TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64)
	{
		TotalProofsFound_UInt64++;
		ProofFound_Flag = true;
		if (TotalProofsFound_UInt64 >= MaxAllowedProofs_UInt64) return;
	}

	switch (InTheorem.Indir_EnumClass)
	{
		case Indirection_EnumClass::_reduce:
		{
			std::for_each(std::execution::par_unseq, 
			Axioms_Vec.begin(), 
			Axioms_Vec.end(), 
			[&](const Axiom_Struct& Axiom)
			{
				while (recursive_calls_available.load(std::memory_order_relaxed) < 3)
					std::this_thread::yield();
					
				recursive_calls_available.fetch_sub(3, std::memory_order_relaxed);
					
				Reduce(TheoremProto_0000, Axiom);
				Reduce(TheoremProto_0001, Axiom);
				Reduce(TheoremProto_0002, Axiom);
					
				recursive_calls_available.fetch_add(3, std::memory_order_relaxed);
			});
			break;
		}

		case Indirection_EnumClass::_expand:
		{
			std::for_each(std::execution::par_unseq, 
			Axioms_Vec.begin(), 
			Axioms_Vec.end(), 
			[&](const Axiom_Struct& Axiom)
			{
				while (recursive_calls_available.load(std::memory_order_relaxed) < 3)
					std::this_thread::yield();
					
				recursive_calls_available.fetch_sub(3, std::memory_order_relaxed);
					
				Expand(TheoremProto_0000, Axiom);
				Expand(TheoremProto_0001, Axiom);
				Expand(TheoremProto_0002, Axiom);
					
				recursive_calls_available.fetch_add(3, std::memory_order_relaxed);
			});
			break;
		}

		case Indirection_EnumClass::_auto:
		default:
		{
			std::for_each(std::execution::par_unseq, 
			Axioms_Vec.begin(), 
			Axioms_Vec.end(), 
			[&](const Axiom_Struct& Axiom)
			{
				while (recursive_calls_available.load(std::memory_order_relaxed) < 6)
					std::this_thread::yield();
					
				recursive_calls_available.fetch_sub(6, std::memory_order_relaxed);
				
				Reduce(TheoremProto_0000, Axiom);
				Reduce(TheoremProto_0001, Axiom);
				Reduce(TheoremProto_0002, Axiom);
				
				Expand(TheoremProto_0000, Axiom);
				Expand(TheoremProto_0001, Axiom);
				Expand(TheoremProto_0002, Axiom);
					
				recursive_calls_available.fetch_add(6, std::memory_order_relaxed);
			});
			break;
		}
	}
};
*/


