#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>
#include <functional>
#include <cstdlib>
#include <array>

enum class RouteSource_EnumClass : int
{
    _lhs,
    _rhs,
    _root
};

enum class Indirection_EnumClass : int
{
    _auto,
    _reduce,
    _expand
};

struct AxiomProto_Struct
{
    uint64_t LHSPrimaryKey_UInt64{};
    uint64_t RHSPrimaryKey_UInt64{};

    std::vector<std::string> LHS_StdStrVec;
    std::vector<std::string> RHS_StdStrVec;

    std::unordered_map<uint64_t, bool> LHSCallHistory;
    std::unordered_map<uint64_t, bool> RHSCallHistory;

    std::unordered_map<RouteSource_EnumClass,
        std::unordered_map<uint64_t, bool>>
        LHSCallGraph_UInt64Map;

    std::unordered_map<RouteSource_EnumClass,
        std::unordered_map<uint64_t, bool>>
        RHSCallGraph_UInt64Map;

    bool SubnetFound_LHS(const uint64_t& PKeyFind) const noexcept
    {
        const bool ret = (LHSPrimaryKey_UInt64 % PKeyFind) == 0;
        return ret;
    }

    bool SubnetFound_RHS(const uint64_t& PKeyFind) const noexcept
    {
        const bool ret = (RHSPrimaryKey_UInt64 % PKeyFind) == 0;
        return ret;
    }

    bool bParseStrict_Flag{};

    uint64_t guid{};
};

struct Theorem_Struct : public AxiomProto_Struct
{
    uint64_t TotalProofsFound_UInt64{};
    uint64_t MaxAllowedProofs_UInt64 = 1;

    bool ProofFound_Flag{};

    std::vector<uint64_t> ProofStack_VecUInt64;

    std::vector<std::string> ProofString_StdStrVec;

    Indirection_EnumClass Indir_EnumClass = Indirection_EnumClass::_auto;

    bool UpdatePrimaryKey_LHS(const uint64_t& PKeyFind, const uint64_t& PKeyReplace) noexcept
    {
        bool ReturnStatus_Flag{};
        LHSPrimaryKey_UInt64 = LHSPrimaryKey_UInt64 / PKeyFind * PKeyReplace;
        ReturnStatus_Flag = true;
        return ReturnStatus_Flag;
    }

    bool UpdatePrimaryKey_RHS(const uint64_t& PKeyFind, const uint64_t& PKeyReplace) noexcept
    {
        bool ReturnStatus_Flag{};
        RHSPrimaryKey_UInt64 = RHSPrimaryKey_UInt64 / PKeyFind * PKeyReplace;
        ReturnStatus_Flag = true;
        return ReturnStatus_Flag;
    }
};

struct Axiom_Struct : public AxiomProto_Struct
{

};

struct NextRound_Struct
{
    bool OddRoundFlag {};
    
    uint8_t NextRound_UInt8 ()
    {
        uint8_t ret {};
        
        if(OddRoundFlag)
        {
            ret = 1;
        }
            
        OddRoundFlag = !OddRoundFlag;
        
        return ret;
    };
};

int main ()
{
    NextRound_Struct Round;
    
    std::array<Theorem_Struct,2> Tasks;
    
    int i = 3;
    
    while(i)
    {
        std::cout << static_cast<unsigned int>(Round.NextRound_UInt8()) << std::endl;
        --i;
    }
    

    return EXIT_SUCCESS;
}
