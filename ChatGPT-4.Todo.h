
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
	  ++TotalProofsFound_UInt64;
		ProofFound_Flag = true;
		if (TotalProofsFound_UInt64 >= MaxAllowedProofs_UInt64) return;
	}

	if (TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64)
	{
      ++TotalProofsFound_UInt64;
		ProofFound_Flag = true;
		if (TotalProofsFound_UInt64 >= MaxAllowedProofs_UInt64) return;
	}

	if (TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64)
	{
	  ++TotalProofsFound_UInt64;
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
                RecursionLimiter::Invoke limiter(3);
                if (limiter.acquired())
    			{	
    				Reduce(TheoremProto_0000, Axiom);
    				Reduce(TheoremProto_0001, Axiom);
    				Reduce(TheoremProto_0002, Axiom);
    				
    				limiter.release();
    			}
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
                RecursionLimiter::Invoke limiter(3);
                if (limiter.acquired())
    			{	
    				Expand(TheoremProto_0000, Axiom);
    				Expand(TheoremProto_0001, Axiom);
    				Expand(TheoremProto_0002, Axiom);
    				
    				limiter.release();
    			}
				
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
                RecursionLimiter::Invoke limiter(6);
                if (limiter.acquired())
    			{
    				Reduce(TheoremProto_0000, Axiom);
    				Reduce(TheoremProto_0001, Axiom);
    				Reduce(TheoremProto_0002, Axiom);
    				
    				Expand(TheoremProto_0000, Axiom);
    				Expand(TheoremProto_0001, Axiom);
    				Expand(TheoremProto_0002, Axiom);
    				
    				limiter.release();
			    }
			});
			break;
		}
	}
};
