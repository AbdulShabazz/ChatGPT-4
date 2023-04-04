
/* Axioms compile an AxiomStack of related subnets. Axioms are added to a GlobalAxiomStack stack */

/*
The Proof modules call an axiom in the GlobalAxiomStack, supplying its latest OutPrimarKey, its 
complementary const PrimaryKey, an indirection, and a initial empty OutProofStack, as input parameters. 
Each asynchronous call is logged in an AxiomHistoryMap object, between rounds. 

This repeats, until a returned primary key matches its complementary primary key (Tentative Proof Found); or the AxiomHistoryMap is full (Proof Failed). 

If a tentative proof is found,the proof is again verified at the vector string token (string) level, 
and compared against its complementary vector string. If verified, a proof is returned. (Q.E.D. - Proof Found)
*/

/*
Each axiom reads the primaryKey into its LocalPrimaryKey and the PrimaryKey from its AxiomStack and attempts to update the LocalPrimaryKey. 
Each successful update is added to the ProofStack. Each access is logged, via its LocalPrimaryKey Proofstack pair, to the GlobalAxiomHistoryMap. 
If the LocalPrimaryKey already exists in the map, then the ProofStack is appended and a proof is marked as found.
*/

/*
If the axiom's LocalAxiomHistoryMap fills w/o a primaryKey update, or both primarykeys match, 
the axiom returns the ProofStack and final state of its PrimaryKey. 
*/
