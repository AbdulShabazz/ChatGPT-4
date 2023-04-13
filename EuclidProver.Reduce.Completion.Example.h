Q:Complete this C++20 Reduce module, 
`
bool ProofFound_Flag{};

uint64_t TotalProofsFound_UInt64{};

uint64_t MaxAllowedProofs_UInt64 = 1;

std::atomic<uint64_t> BreadthFirstSearchDepth_UInt64{0};

__attribute__((always_inline))
void Reduce(Theorem_Struct InTheorem, const Axiom_Struct InAxiom)
{
    /*
    1. TotalProofsFound_UInt64 < MaxAllowedProofs_UInt64 ?
       no: return
    2. axiom.guid in theorem.RHSReduceCallGraph_UInt64Map ?
       no: return
       yes: axiom.guid in theorem.RHSReduceCallHistory_UInt64Map ?
          y: return
          n: add guid to theorem.RHSReduceCallHistory_UInt64Map
             3. calculate new Primarykey permutations for InTheorem: lhs only; rhs only; lhs + rhs:
    */
    Theorem_Struct TheoremProto_0000 = InTheorem;
    Theorem_Struct TheoremProto_0001 = InTheorem;
    Theorem_Struct TheoremProto_0002 = InTheorem;
    
    TheoremProto_0000.UpdatePrimaryKey_LHS(InAxiom.LHSPrimaryKey_UInt64, InAxiom.RHSPrimaryKey_UInt64);
    
    TheoremProto_0001.UpdatePrimaryKey_RHS(InAxiom.LHSPrimaryKey_UInt64, InAxiom.RHSPrimaryKey_UInt64);
    
    TheoremProto_0002.UpdatePrimaryKey_LHS(InAxiom.LHSPrimaryKey_UInt64, InAxiom.RHSPrimaryKey_UInt64);
    TheoremProto_0002.UpdatePrimaryKey_RHS(InAxiom.LHSPrimaryKey_UInt64, InAxiom.RHSPrimaryKey_UInt64);
    /*
    /*       4. TheoremProto_0000.ProofStack_VecUInt64.push_back(axiom.guid)
                TheoremProto_0001.ProofStack_VecUInt64.push_back(axiom.guid)
                TheoremProto_0002.ProofStack_VecUInt64.push_back(axiom.guid)
             5. TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64 ?
                y: TotalProofsFound_UInt64++
                   ProofFound_Flag = true;
                   return
                n: Test TheoremProto_0001:
                    6. TheoremProto_0001.LHSPrimaryKey_UInt64 == TheoremProto_0001.RHSPrimaryKey_UInt64 ?
                        y: TotalProofsFound_UInt64++
                           ProofFound_Flag = true;
                           TotalProofsFound_UInt64 < MaxAllowedProofs_UInt64 ?
                           y: Test TheoremProto_0002...
                           n: return
                        n: Test TheoremProto_0002:
                            7. TheoremProto_0002.LHSPrimaryKey_UInt64 == TheoremProto_0002.RHSPrimaryKey_UInt64 ?
                                y: TotalProofsFound_UInt64++
                                   ProofFound_Flag = true;
                                   return
                                n: Next round:
                                	switch(Theorem.Indir_EnumClass)
                                	{
                                	    case Indirection_EnumClass::_reduce:
                                	    {
                                        	for(Axiom_Struct& Axiom : Axioms_Vec)
                                        	{
                                    	        Reduce(Theorem, Axiom);
                                        	}
                                	        break;   
                                	    }
                                	    
                                	    case Indirection_EnumClass::_expand:
                                	    {
                                        	for(Axiom_Struct& Axiom : Axioms_Vec)
                                        	{
                                    	        Expand(Theorem, Axiom);
                                        	}
                                	        break;
                                	    }
                                	    
                                	    case Indirection_EnumClass::_auto:
                                	    default:
                                	    {
                                        	for(Axiom_Struct& Axiom : Axioms_Vec)
                                        	{
                                    	        Reduce(Theorem, Axiom);
                                    	        Expand(Theorem, Axiom);
                                        	}
                                	        break;
                                	    }
                                	} 
     
	std::cout << "Invoke: Expand(...) : InAxiom.guid: " << InAxiom.guid << std::endl;
};
`. Ignore any external declarations. Focus only on the module.

To complete the Reduce module, you need to finish implementing the logic for the steps 4-7 in the comments. I've added the missing code segments to complete the Reduce function:

cpp
*/

__attribute__((always_inline))
void Reduce(Theorem_Struct InTheorem, const Axiom_Struct InAxiom)
{
    if (TotalProofsFound_UInt64 >= MaxAllowedProofs_UInt64) return;

    if (InTheorem.RHSReduceCallGraph_UInt64Map.count(InAxiom.guid) == 0) return;

    if (InTheorem.RHSReduceCallHistory_UInt64Map.count(InAxiom.guid) > 0) return;

    InTheorem.RHSReduceCallHistory_UInt64Map.insert(InAxiom.guid);

    Theorem_Struct TheoremProto_0000 = InTheorem;
    Theorem_Struct TheoremProto_0001 = InTheorem;
    Theorem_Struct TheoremProto_0002 = InTheorem;

    TheoremProto_0000.UpdatePrimaryKey_LHS(InAxiom.LHSPrimaryKey_UInt64, InAxiom.RHSPrimaryKey_UInt64);

    TheoremProto_0001.UpdatePrimaryKey_RHS(InAxiom.LHSPrimaryKey_UInt64, InAxiom.RHSPrimaryKey_UInt64);

    TheoremProto_0002.UpdatePrimaryKey_LHS(InAxiom.LHSPrimaryKey_UInt64, InAxiom.RHSPrimaryKey_UInt64);
    TheoremProto_0002.UpdatePrimaryKey_RHS(InAxiom.LHSPrimaryKey_UInt64, InAxiom.RHSPrimaryKey_UInt64);

    TheoremProto_0000.ProofStack_VecUInt64.push_back(InAxiom.guid);
    TheoremProto_0001.ProofStack_VecUInt64.push_back(InAxiom.guid);
    TheoremProto_0002.ProofStack_VecUInt64.push_back(InAxiom.guid);

    if (TheoremProto_0000.LHSPrimaryKey_UInt64 == TheoremProto_0000.RHSPrimaryKey_UInt64)
    {
        TotalProofsFound_UInt64++;
        ProofFound_Flag = true;
        return;
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
        return;
    }

    switch (InTheorem.Indir_EnumClass)
    {
        case Indirection_EnumClass::_reduce:
        {
            for (Axiom_Struct& Axiom : Axioms_Vec)
            {
                Reduce(TheoremProto_0002, Axiom);
            }
            break;
        }

        case Indirection_EnumClass::_expand:
        {
            for (Axiom_Struct& Axiom : Axioms_Vec)
            {
                Expand(TheoremProto_0002, Axiom);
            }
            break;
        }

        case Indirection_EnumClass::_auto:
        default:
        {
            for (Axiom_Struct& Axiom : Axioms_Vec)
            {
                Reduce(TheoremProto_0002, Axiom);
                Expand(TheoremProto_0002, Axiom);
            }
            break;
        }
    }
std::cout << "Invoke: Expand(...) : InAxiom.guid: " << InAxiom.guid << std::endl;
}

/* 

Q:Continue.

With this, the `Reduce` module is now complete. It takes a `Theorem_Struct` object and an `Axiom_Struct` object as input, and processes them according to the algorithm outlined in the comments. If a proof is found, it updates the `TotalProofsFound_UInt64` counter and sets the `ProofFound_Flag` to `true`. The function returns early if certain conditions are met, such as the maximum allowed number of proofs being found.

In addition, the `Reduce` function takes into account the `Indir_EnumClass` enumeration value of the theorem and invokes the appropriate functions for the next round of processing, which may include calling `Reduce`, `Expand`, or both.
 */
