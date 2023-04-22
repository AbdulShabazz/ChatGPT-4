#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>
#include <functional>
#include <cstdlib>
#include <array>
#include <chrono>

enum class MaxCPUCores : int
{
    _1,
    _Max,
    _GPU_Enabled
};

enum class RouteGoal_EnumClass : int
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

    std::unordered_map<RouteGoal_EnumClass,
        std::unordered_map<uint64_t, bool>>
        LHSCallGraph_UInt64Map;

    std::unordered_map<RouteGoal_EnumClass,
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
    
    uint8_t CurrentRound_UInt8 ()
    {
        uint8_t ret {1};
        
        if(OddRoundFlag)
        {
            ret = 0;
        }
        
        return ret;
    };
};

uint64_t GUID {};

int main ()
{
    const auto start_time_chrono = std::chrono::high_resolution_clock::now();

    /*
    token: [ "1" "2" "4" "+" ]
    prime: [  2   3   5   7 ]
    */

    Theorem_Struct Theorem;

    const uint64_t N = 2; // Update as needed;

    std::array < Axiom_Struct, N > Axioms_Vec;
    
    std::unordered_map <uint64_t,Axiom_Struct> Axioms_LibraryMap;
    
    std::vector<std::array<uint64_t, 2>> Axioms_UInt64Vec = // const (global) task list
    {
        {//std::vector<uint64_t> _1p1p1p1e4 =
            5488, // "1 + 1 + 1 + 1"
            5 // "4"
        },//;

        {//std::vector<uint64_t> _1p1e2 =
            28, // "1 + 1"
            3 // "2"
        },//;

        {//std::vector<uint64_t> _2p2e4 =
            63, // "2 + 2"
            5 // "4"
        }
    };
    
    for (const std::array<uint64_t, 2>&Axiom_i : Axioms_UInt64Vec)
    {
        uint64_t  lhs = Axiom_i[0];
        uint64_t  rhs = Axiom_i[1];

        const uint64_t _lhs = Axiom_i[0];
        const uint64_t _rhs = Axiom_i[1];

        if (_lhs < _rhs)
        {
            lhs = _rhs;
            rhs = _lhs;
        }

        if (GUID < 1)
        {
            Theorem.guid = ++GUID;
            Theorem.LHSPrimaryKey_UInt64 = lhs;
            Theorem.RHSPrimaryKey_UInt64 = rhs;
            continue;
        }

        Axiom_Struct Axiom;
        Axiom.guid = ++GUID;
        Axiom.LHSPrimaryKey_UInt64 = lhs;
        Axiom.RHSPrimaryKey_UInt64 = rhs;

        /*
        Authorize qualifying axiom subnets by adding
        their netlists to the outbound route map
        */

        if (Theorem.SubnetFound_LHS(lhs))
        {
            Theorem.LHSCallGraph_UInt64Map[RouteGoal_EnumClass::_rhs][Axiom.guid] = true;
        }

        if (Theorem.SubnetFound_LHS(rhs))
        {
            Theorem.LHSCallGraph_UInt64Map[RouteGoal_EnumClass::_lhs][Axiom.guid] = true;
        }

        if (Theorem.SubnetFound_RHS(lhs))
        {
            Theorem.RHSCallGraph_UInt64Map[RouteGoal_EnumClass::_rhs][Axiom.guid] = true;
        }

        if (Theorem.SubnetFound_RHS(rhs))
        {
            Theorem.RHSCallGraph_UInt64Map[RouteGoal_EnumClass::_lhs][Axiom.guid] = true;
        }

        Axioms_LibraryMap[Axiom.guid - 1] = Axiom;
        
        Axioms_Vec[Axiom.guid - 1] = Axiom;
    }

    for (Axiom_Struct& Axiom_i : Axioms_Vec)
    {
        for (const Axiom_Struct& Axiom_j : Axioms_Vec)
        {
            /*
            Authorize qualifying axiom subnets by adding
            their netlists to the outbound route map
            */
            const bool ijAvoidsACallLoop_Flag = (Axiom_i.guid != Axiom_j.guid); // Avoid Call loops
            if (ijAvoidsACallLoop_Flag)
            {
                if (Axiom_i.SubnetFound_LHS(Axiom_j.LHSPrimaryKey_UInt64))
                {
                    Axiom_i.LHSCallGraph_UInt64Map[RouteGoal_EnumClass::_rhs][Axiom_j.guid] = true;
                }

                if (Axiom_i.SubnetFound_LHS(Axiom_j.RHSPrimaryKey_UInt64))
                {
                    Axiom_i.LHSCallGraph_UInt64Map[RouteGoal_EnumClass::_lhs][Axiom_j.guid] = true;
                }

                if (Axiom_i.SubnetFound_RHS(Axiom_j.LHSPrimaryKey_UInt64))
                {
                    Axiom_i.RHSCallGraph_UInt64Map[RouteGoal_EnumClass::_rhs][Axiom_j.guid] = true;
                }

                if (Axiom_i.SubnetFound_RHS(Axiom_j.RHSPrimaryKey_UInt64))
                {
                    Axiom_i.LHSCallGraph_UInt64Map[RouteGoal_EnumClass::_rhs][Axiom_j.guid] = true;
                }
            }
        }
    }
    
    for (Axiom_Struct& Axiom_i : Axioms_Vec)
    {
        Axioms_LibraryMap[Axiom_i.guid] = Axiom_i;
    }
    
    NextRound_Struct Round;
    
    //std::vector<Theorem_Struct> InOut;
    
    std::array < std::vector < Theorem_Struct >,2 > Tasks_Thread;
    
    Tasks_Thread[0].push_back(Theorem);
    
    /*
    int i = 3;
    
    while(i)
    {
        std::cout << static_cast<unsigned int>(Round.NextRound_UInt8()) << std::endl;
        --i;
    }
    */
    
    uint8_t ProofStage_UInt8 = 0;
    
    uint64_t MaxAllowedProofs_UInt64 {1};
    uint64_t TotalProofsFound_UInt64 {};
    
    //while(Tasks_Thread[i].size())
    //{
        const uint8_t Read = Round.NextRound_UInt8();
        const uint8_t Write = Round.CurrentRound_UInt8();
        
        for(Theorem_Struct InTheorem : Tasks_Thread[Read])
        {
            if(InTheorem.LHSPrimaryKey_UInt64 == InTheorem.RHSPrimaryKey_UInt64)
            {
                for(const uint64_t& nID_UInt64 : InTheorem.ProofStack_VecUInt64)
                {
                    std::cout << "Axiom_" << static_cast<uint64_t>(nID_UInt64) << std::endl;
                }
                
                std::cout << "\n\n";
                std::cout << "Q.E.D.";
                
                ++TotalProofsFound_UInt64;
                if(TotalProofsFound_UInt64 >= MaxAllowedProofs_UInt64)
                    break;
            }
            
            switch(InTheorem.Indir_EnumClass)
            {
                case Indirection_EnumClass::_reduce:
                if(
                    InTheorem.LHSCallGraph_UInt64Map.find(RouteGoal_EnumClass::_rhs) != 
                    InTheorem.LHSCallGraph_UInt64Map.begin()
                   )
               {
                    for(const auto& idx_pair : InTheorem.LHSCallGraph_UInt64Map [ RouteGoal_EnumClass :: _rhs ] )
                    {
                        const uint64_t& idx_UInt64 = idx_pair.first;
                        
                        if(InTheorem.LHSCallHistory.find(idx_UInt64) != 
                        InTheorem.LHSCallHistory.begin())
                            continue;
                            
                        InTheorem.LHSCallHistory[ idx_UInt64 ] = true;
                        
                        const Axiom_Struct& Axiom = Axioms_LibraryMap [ idx_UInt64 ];
                        
                        InTheorem.ProofStack_VecUInt64.push_back(Axiom.guid);
                        
                        Theorem_Struct th_0000 = InTheorem;
                        Theorem_Struct th_0001 = InTheorem;
                        Theorem_Struct th_0002 = InTheorem;
                        
                        th_0000.UpdatePrimaryKey_LHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0001.UpdatePrimaryKey_RHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_LHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_RHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        
                        th_0000.LHSCallGraph_UInt64Map = 
                        th_0001.LHSCallGraph_UInt64Map = 
                        th_0002.LHSCallGraph_UInt64Map = 
                            Axiom.LHSCallGraph_UInt64Map;
                        
                        th_0000.RHSCallGraph_UInt64Map = 
                        th_0001.RHSCallGraph_UInt64Map = 
                        th_0002.RHSCallGraph_UInt64Map = 
                            Axiom.RHSCallGraph_UInt64Map;
                        
                        Tasks_Thread[Write].push_back(th_0000);
                        Tasks_Thread[Write].push_back(th_0001);
                        Tasks_Thread[Write].push_back(th_0002);
                    }
               }
                if(
                    InTheorem.RHSCallGraph_UInt64Map.find(RouteGoal_EnumClass::_rhs) != 
                    InTheorem.RHSCallGraph_UInt64Map.begin()
                   )
               {
                    for(const auto& idx_pair : InTheorem.LHSCallGraph_UInt64Map [ RouteGoal_EnumClass :: _rhs ] )
                    {
                        const uint64_t& idx_UInt64 = idx_pair.first;
                        
                        if(InTheorem.RHSCallHistory.find(idx_UInt64) != 
                        InTheorem.LHSCallHistory.begin())
                            continue;
                            
                        InTheorem.RHSCallHistory[ idx_UInt64 ] = true;
                        
                        const Axiom_Struct& Axiom = Axioms_LibraryMap [ idx_UInt64 ];
                        
                        InTheorem.ProofStack_VecUInt64.push_back(Axiom.guid);
                        
                        Theorem_Struct th_0000 = InTheorem;
                        Theorem_Struct th_0001 = InTheorem;
                        Theorem_Struct th_0002 = InTheorem;
                        
                        th_0000.UpdatePrimaryKey_LHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0001.UpdatePrimaryKey_RHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_LHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_RHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        
                        th_0000.LHSCallGraph_UInt64Map = 
                        th_0001.LHSCallGraph_UInt64Map = 
                        th_0002.LHSCallGraph_UInt64Map = 
                            Axiom.LHSCallGraph_UInt64Map;
                        
                        th_0000.RHSCallGraph_UInt64Map = 
                        th_0001.RHSCallGraph_UInt64Map = 
                        th_0002.RHSCallGraph_UInt64Map = 
                            Axiom.RHSCallGraph_UInt64Map;
                        
                        Tasks_Thread[Write].push_back(th_0000);
                        Tasks_Thread[Write].push_back(th_0001);
                        Tasks_Thread[Write].push_back(th_0002);
                    }
               }
                break;
                
                case Indirection_EnumClass::_expand:
                if(
                    InTheorem.LHSCallGraph_UInt64Map.find(RouteGoal_EnumClass::_lhs) != 
                    InTheorem.LHSCallGraph_UInt64Map.begin()
                   )
               {
                    for(const auto& idx_pair : InTheorem.LHSCallGraph_UInt64Map [ RouteGoal_EnumClass :: _lhs ] )
                    {
                        const uint64_t& idx_UInt64 = idx_pair.first;
                        
                        if(InTheorem.LHSCallHistory.find(idx_UInt64) != 
                        InTheorem.LHSCallHistory.begin())
                            continue;
                            
                        InTheorem.LHSCallHistory[ idx_UInt64 ] = true;
                        
                        const Axiom_Struct& Axiom = Axioms_LibraryMap [ idx_UInt64 ];
                        
                        InTheorem.ProofStack_VecUInt64.push_back(Axiom.guid);
                        
                        Theorem_Struct th_0000 = InTheorem;
                        Theorem_Struct th_0001 = InTheorem;
                        Theorem_Struct th_0002 = InTheorem;
                        
                        th_0000.UpdatePrimaryKey_LHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0001.UpdatePrimaryKey_RHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_LHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_RHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        
                        th_0000.LHSCallGraph_UInt64Map = 
                        th_0001.LHSCallGraph_UInt64Map = 
                        th_0002.LHSCallGraph_UInt64Map = 
                            Axiom.LHSCallGraph_UInt64Map;
                        
                        th_0000.RHSCallGraph_UInt64Map = 
                        th_0001.RHSCallGraph_UInt64Map = 
                        th_0002.RHSCallGraph_UInt64Map = 
                            Axiom.RHSCallGraph_UInt64Map;
                        
                        Tasks_Thread[Write].push_back(th_0000);
                        Tasks_Thread[Write].push_back(th_0001);
                        Tasks_Thread[Write].push_back(th_0002);
                    }
               }
                if(
                    InTheorem.RHSCallGraph_UInt64Map.find(RouteGoal_EnumClass::_lhs) != 
                    InTheorem.RHSCallGraph_UInt64Map.begin()
                   )
               {
                    for(const auto& idx_pair : InTheorem.LHSCallGraph_UInt64Map [ RouteGoal_EnumClass :: _lhs ] )
                    {
                        const uint64_t& idx_UInt64 = idx_pair.first;
                        
                        if(InTheorem.RHSCallHistory.find(idx_UInt64) != 
                        InTheorem.LHSCallHistory.begin())
                            continue;
                            
                        InTheorem.RHSCallHistory[ idx_UInt64 ] = true;
                        
                        const Axiom_Struct& Axiom = Axioms_LibraryMap [ idx_UInt64 ];
                        
                        InTheorem.ProofStack_VecUInt64.push_back(Axiom.guid);
                        
                        Theorem_Struct th_0000 = InTheorem;
                        Theorem_Struct th_0001 = InTheorem;
                        Theorem_Struct th_0002 = InTheorem;
                        
                        th_0000.UpdatePrimaryKey_LHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0001.UpdatePrimaryKey_RHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_LHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_RHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        
                        th_0000.LHSCallGraph_UInt64Map = 
                        th_0001.LHSCallGraph_UInt64Map = 
                        th_0002.LHSCallGraph_UInt64Map = 
                            Axiom.LHSCallGraph_UInt64Map;
                        
                        th_0000.RHSCallGraph_UInt64Map = 
                        th_0001.RHSCallGraph_UInt64Map = 
                        th_0002.RHSCallGraph_UInt64Map = 
                            Axiom.RHSCallGraph_UInt64Map;
                        
                        Tasks_Thread[Write].push_back(th_0000);
                        Tasks_Thread[Write].push_back(th_0001);
                        Tasks_Thread[Write].push_back(th_0002);
                    }
               }
                break;
                
                case Indirection_EnumClass::_auto:
                default:
                if(
                    InTheorem.LHSCallGraph_UInt64Map.find(RouteGoal_EnumClass::_rhs) != 
                    InTheorem.LHSCallGraph_UInt64Map.begin()
                   )
               {
                    for(const auto& idx_pair : InTheorem.LHSCallGraph_UInt64Map [ RouteGoal_EnumClass :: _rhs ] )
                    {
                        const uint64_t& idx_UInt64 = idx_pair.first;
                        
                        if(InTheorem.LHSCallHistory.find(idx_UInt64) != 
                        InTheorem.LHSCallHistory.begin())
                            continue;
                            
                        InTheorem.LHSCallHistory[ idx_UInt64 ] = true;
                        
                        const Axiom_Struct& Axiom = Axioms_LibraryMap [ idx_UInt64 ];
                        
                        InTheorem.ProofStack_VecUInt64.push_back(Axiom.guid);
                        
                        Theorem_Struct th_0000 = InTheorem;
                        Theorem_Struct th_0001 = InTheorem;
                        Theorem_Struct th_0002 = InTheorem;
                        
                        th_0000.UpdatePrimaryKey_LHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0001.UpdatePrimaryKey_RHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_LHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_RHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        
                        th_0000.LHSCallGraph_UInt64Map = 
                        th_0001.LHSCallGraph_UInt64Map = 
                        th_0002.LHSCallGraph_UInt64Map = 
                            Axiom.LHSCallGraph_UInt64Map;
                        
                        th_0000.RHSCallGraph_UInt64Map = 
                        th_0001.RHSCallGraph_UInt64Map = 
                        th_0002.RHSCallGraph_UInt64Map = 
                            Axiom.RHSCallGraph_UInt64Map;
                        
                        Tasks_Thread[Write].push_back(th_0000);
                        Tasks_Thread[Write].push_back(th_0001);
                        Tasks_Thread[Write].push_back(th_0002);
                    }
               }
                if(
                    InTheorem.RHSCallGraph_UInt64Map.find(RouteGoal_EnumClass::_rhs) != 
                    InTheorem.RHSCallGraph_UInt64Map.begin()
                   )
               {
                    for(const auto& idx_pair : InTheorem.RHSCallGraph_UInt64Map [ RouteGoal_EnumClass :: _rhs ] )
                    {
                        const uint64_t& idx_UInt64 = idx_pair.first;
                        
                        if(InTheorem.RHSCallHistory.find(idx_UInt64) != 
                        InTheorem.LHSCallHistory.begin())
                            continue;
                            
                        InTheorem.RHSCallHistory[ idx_UInt64 ] = true;
                        
                        const Axiom_Struct& Axiom = Axioms_LibraryMap [ idx_UInt64 ];
                        
                        InTheorem.ProofStack_VecUInt64.push_back(Axiom.guid);
                        
                        Theorem_Struct th_0000 = InTheorem;
                        Theorem_Struct th_0001 = InTheorem;
                        Theorem_Struct th_0002 = InTheorem;
                        
                        th_0000.UpdatePrimaryKey_LHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0001.UpdatePrimaryKey_RHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_LHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_RHS(Axiom.LHSPrimaryKey_UInt64, Axiom.RHSPrimaryKey_UInt64);
                        
                        th_0000.LHSCallGraph_UInt64Map = 
                        th_0001.LHSCallGraph_UInt64Map = 
                        th_0002.LHSCallGraph_UInt64Map = 
                            Axiom.LHSCallGraph_UInt64Map;
                        
                        th_0000.RHSCallGraph_UInt64Map = 
                        th_0001.RHSCallGraph_UInt64Map = 
                        th_0002.RHSCallGraph_UInt64Map = 
                            Axiom.RHSCallGraph_UInt64Map;
                        
                        Tasks_Thread[Write].push_back(th_0000);
                        Tasks_Thread[Write].push_back(th_0001);
                        Tasks_Thread[Write].push_back(th_0002);
                    }
               }
                if(
                    InTheorem.LHSCallGraph_UInt64Map.find(RouteGoal_EnumClass::_lhs) != 
                    InTheorem.LHSCallGraph_UInt64Map.begin()
                   )
               {
                    for(const auto& idx_pair : InTheorem.LHSCallGraph_UInt64Map [ RouteGoal_EnumClass :: _lhs ] )
                    {
                        const uint64_t& idx_UInt64 = idx_pair.first;
                        
                        if(InTheorem.LHSCallHistory.find(idx_UInt64) != 
                        InTheorem.LHSCallHistory.begin())
                            continue;
                            
                        InTheorem.LHSCallHistory[ idx_UInt64 ] = true;
                        
                        const Axiom_Struct& Axiom = Axioms_LibraryMap [ idx_UInt64 ];
                        
                        InTheorem.ProofStack_VecUInt64.push_back(Axiom.guid);
                        
                        Theorem_Struct th_0000 = InTheorem;
                        Theorem_Struct th_0001 = InTheorem;
                        Theorem_Struct th_0002 = InTheorem;
                        
                        th_0000.UpdatePrimaryKey_LHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0001.UpdatePrimaryKey_RHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_LHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_RHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        
                        th_0000.LHSCallGraph_UInt64Map = 
                        th_0001.LHSCallGraph_UInt64Map = 
                        th_0002.LHSCallGraph_UInt64Map = 
                            Axiom.LHSCallGraph_UInt64Map;
                        
                        th_0000.RHSCallGraph_UInt64Map = 
                        th_0001.RHSCallGraph_UInt64Map = 
                        th_0002.RHSCallGraph_UInt64Map = 
                            Axiom.RHSCallGraph_UInt64Map;
                        
                        Tasks_Thread[Write].push_back(th_0000);
                        Tasks_Thread[Write].push_back(th_0001);
                        Tasks_Thread[Write].push_back(th_0002);
                    }
               }
                if(
                    InTheorem.RHSCallGraph_UInt64Map.find(RouteGoal_EnumClass::_lhs) != 
                    InTheorem.RHSCallGraph_UInt64Map.begin()
                   )
               {
                    for(const auto& idx_pair : InTheorem.RHSCallGraph_UInt64Map [ RouteGoal_EnumClass :: _lhs ] )
                    {
                        const uint64_t& idx_UInt64 = idx_pair.first;
                        
                        if(InTheorem.RHSCallHistory.find(idx_UInt64) != 
                        InTheorem.LHSCallHistory.begin())
                            continue;
                            
                        InTheorem.RHSCallHistory[ idx_UInt64 ] = true;
                        
                        const Axiom_Struct& Axiom = Axioms_LibraryMap [ idx_UInt64 ];
                        
                        InTheorem.ProofStack_VecUInt64.push_back(Axiom.guid);
                        
                        Theorem_Struct th_0000 = InTheorem;
                        Theorem_Struct th_0001 = InTheorem;
                        Theorem_Struct th_0002 = InTheorem;
                        
                        th_0000.UpdatePrimaryKey_LHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0001.UpdatePrimaryKey_RHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_LHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        th_0002.UpdatePrimaryKey_RHS(Axiom.RHSPrimaryKey_UInt64, Axiom.LHSPrimaryKey_UInt64);
                        
                        th_0000.LHSCallGraph_UInt64Map = 
                        th_0001.LHSCallGraph_UInt64Map = 
                        th_0002.LHSCallGraph_UInt64Map = 
                            Axiom.LHSCallGraph_UInt64Map;
                        
                        th_0000.RHSCallGraph_UInt64Map = 
                        th_0001.RHSCallGraph_UInt64Map = 
                        th_0002.RHSCallGraph_UInt64Map = 
                            Axiom.RHSCallGraph_UInt64Map;
                        
                        Tasks_Thread[Write].push_back(th_0000);
                        Tasks_Thread[Write].push_back(th_0001);
                        Tasks_Thread[Write].push_back(th_0002);
                    }
               }
                break;
            } // switch(InTheorem.Indirection_EnumClass)
        } // for(_ : Tasks_Thread[i])
        Tasks_Thread[Read] = {};
    //}
    
    return EXIT_SUCCESS;
}
