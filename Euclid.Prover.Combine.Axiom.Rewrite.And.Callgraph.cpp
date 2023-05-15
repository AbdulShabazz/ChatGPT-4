/*Q:Combine these two c++20 modules into a single for-loop: Module_0000 maps primes back to symbols to verify proofs, Module_0001 uses primes to quickly find tentative proofs.*/
__stdtracein__("ProofVerified");
bool ReturnStatusFlag{ true };
OutTheoremStdStrVec.emplace_back (InTheoremStdStrVec);

std::vector<
std::vector<
std::string>>
TempTheoremStdStrVec{ InTheoremStdStrVec };

std::vector<
std::string>
TempAxiomCommitLogStdStrVecRef;

std::size_t i { ProofStackUInt64 };

for (const auto& Axiom : Axioms_UInt64Vec)
{
    const auto& AxiomLHS = Axiom[LHS];
    const auto& AxiomRHS = Axiom[RHS];

    while (i < InTheoremUInt64.size ())
    {
        if (!ReturnStatusFlag)
            return ReturnStatusFlag;

        const std::size_t& opcode = std::size_t{ InTheoremUInt64[i++] };
        const std::size_t& guid = std::size_t{ InTheoremUInt64[i++] - 1 };

        switch (opcode)
        {
            case 0x00:
            { // "lhsreduce" operation //
                if (TempTheoremStdStrVec[LHS] % AxiomLHS == 0) {
                    __stdlog__({ "lhs_reduce via Axiom_", std::to_string(guid) });
                    ReturnStatusFlag =
                        Rewrite (TempTheoremStdStrVec[LHS], InAxiomsStdStrVec[guid][LHS], InAxiomsStdStrVec[guid][RHS]);
                    TempAxiomCommitLogStdStrVecRef.emplace_back ("lhs_reduce via Axiom_" + std::to_string (guid));
                }
                break;
            }
            case 0x01:
            { // "lhsexpand" operation //
                if (TempTheoremStdStrVec[LHS] % AxiomRHS == 0) {
                    __stdlog__({ "lhs_expand via Axiom_", std::to_string(guid) });
                    ReturnStatusFlag =
                        Rewrite (TempTheoremStdStrVec[LHS], InAxiomsStdStrVec[guid][RHS], InAxiomsStdStrVec[guid][LHS]);
                    TempAxiomCommitLogStdStrVecRef.emplace_back ("lhs_expand via Axiom_" + std::to_string (guid));
                }
                break;
            }
            case 0x02:
            { // "rhsreduce" operation //
                if (TempTheoremStdStrVec[RHS] % AxiomLHS == 0) {
                    __stdlog__({ "rhs_reduce via Axiom_", std::to_string(guid) });
                    ReturnStatusFlag =
                        Rewrite (TempTheoremStdStrVec[RHS], InAxiomsStdStrVec[guid][LHS], InAxiomsStdStrVec[guid][RHS]);
                    TempAxiomCommitLogStdStrVecRef.emplace_back ("rhs_reduce via Axiom_" + std::to_string (guid));
                }
                break;
            }
            case 0x03:
            { // "rhsexpand" operation //
                if (TempTheoremStdStrVec[RHS] % AxiomRHS == 0) {
                    __stdlog__({ "rhs_expand via Axiom_", std::to_string(guid) });
                    ReturnStatusFlag =
                        Rewrite (TempTheoremStdStrVec[RHS], InAxiomsStdStrVec[guid][RHS], InAxiomsStdStrVec[guid][LHS]);
                    TempAxiomCommitLogStdStrVecRef.emplace_back
