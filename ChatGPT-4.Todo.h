#include <vector>
#include <chrono>
#include <iostream>
#include <thread>
#include <variant>
#include <unordered_map>
#include <functional>
#include <execution>
#include <stop_token>
#include <thread>
#include <future>
#include <mutex>
#include <algorithm>
#include <cstdint>
#include <sys/resource.h>

using namespace std;

int main()
{
	const auto start_time_chrono = std::chrono::high_resolution_clock::now();
	
	enum class Indirection_EnumClass : uint64_t
    {
    	_auto,
    	_reduce,
    	_expand
    };
    
    struct AxiomProto_Struct
    {
        std::unordered_map<uint64_t,bool> LHSCallGraph_UInt64Map;
        std::unordered_map<uint64_t,bool> RHSCallGraph_UInt64Map;
        
        uint64_t guid{};
    };
    
    struct Theorem_Struct : public AxiomProto_Struct
    {
        uint64_t LHSPrimaryKey_UInt64{};
        uint64_t RHSPrimaryKey_UInt64{};
        uint64_t TotalProofsFound_UInt64{};
        uint64_t MaxAllowedProofs_UInt64 = 1;
        
        bool ProofFound_Flag{};
        
        std::vector<uint64_t> ProofStack_VecUInt64;
        
        std::vector<std::string> LHS_StdStrVec;
        std::vector<std::string> RHS_StdStrVec;
        std::vector<std::string> ProofString_StdStrVec;
        
        Indirection_EnumClass Indir_EnumClass = Indirection_EnumClass::_auto;
        
        bool SubkeyFOUND_LHS(const uint64_t& PKeyFind) const;
        {
            const bool ret = ((LHSPrimaryKey_UInt64 >= PKeyFind) && 
                             ((LHSPrimaryKey_UInt64 % PKeyFind) == 0));
            return ret;
        }
        
        bool SubkeyFOUND_RHS(const uint64_t& PKeyFind) const;
        {
            const bool ret = ((RHSPrimaryKey_UInt64 >= PKeyFind) && 
                             ((RHSPrimaryKey_UInt64 % PKeyFind) == 0));
            return ret;
        }
        
        bool UpdatePrimaryKey_LHS(const uint64_t& PKeyFind, const uint64_t& PKeyReplacement)
        {
            bool ReturnStatus_Flag{};
            LHSPrimaryKey_UInt64 = LHSPrimaryKey_UInt64 / PKeyFind * PKeyReplacement;
            ReturnStatus_Flag = true;
            return ReturnStatus_Flag;
        }
        
        bool UpdatePrimaryKey_RHS(const uint64_t& PKeyFind, const uint64_t& PKeyReplacement)
        {
            bool ReturnStatus_Flag{};
            RHSPrimaryKey_UInt64 = RHSPrimaryKey_UInt64 / PKeyFind * PKeyReplacement;
            ReturnStatus_Flag = true;
            return ReturnStatus_Flag;
        }
    };
    
    struct Axiom_Struct : public AxiomProto_Struct
    {
        uint64_t PrimaryKey_UInt64{};
        
        bool bParseStrict_Flag = false;
        
        bool SubkeyFOUND(const uint64_t& PKeyFind) const;
        {
            const bool ret = ((PrimaryKey_UInt64 % PKeyFind) == 0);
            return ret;
        }
        
        bool UpdatePrimaryKey_UInt64(const uint64_t& PKeyFind, const uint64_t& PKeyReplacement)
        {
            bool ReturnStatus_Flag{};
            PrimaryKey_UInt64 = PrimaryKey_UInt64 / PKeyFind * PKeyReplacement;
            ReturnStatus_Flag = true;
            return ReturnStatus_Flag;
        }
    };
	
	/*
	token: [ 1 2 4 '+' ]
	prime: [ 2 3 5 7 ]
	*/
	std::vector<std::vector<uint64_t>> Prove =
	{
		{//std::vector<uint64_t> _1p1p1p1e4 =
			5488, // 1 + 1 + 1 + 1
			5 // 4
		},//;
	};

	std::vector<std::vector<uint64_t>> Axioms_UInt64Vec = // const (global) task list
	{
		{//std::vector<uint64_t> _1p1p1p1e4 =
			5488, // 1 + 1 + 1 + 1
			5 // 4
		},//;
		
		{//std::vector<uint64_t> _1p1e2 =
			28, // 1 + 1
			3 // 2
		},//;
		
		{//std::vector<uint64_t> _2p2e4 =
			63, // 2 + 2
			5 // 4
		}
	};
	
	/*
    Total Duration (nanoseconds): 53455
    LHSReduceCallGraph_UInt64Map[0][1] = true
    LHSExpandCallGraph_UInt64Map[2][1] = true
    RHSExpandCallGraph_UInt64Map[2][0] = true
    RHSExpandCallGraph_UInt64Map[0][2] = true
	*/

    using Map = std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>>;
	Map LHSCallGraph_UInt64Map;
	Map RHSCallGraph_UInt64Map;

    uint64_t GUID = 0;

	Theorem_Struct Theorem;
	
	Theorem.guid = GUID++;
	Theorem.LHSPrimaryKey_UInt64 = Axioms_UInt64Vec[0][0];
	Theorem.RHSPrimaryKey_UInt64 = Axioms_UInt64Vec[0][1];

    Axioms_UInt64Vec.erase(0);

	std::vector<Axiom_Struct> Axioms_Vec;
	Axioms_Vec.resize(Axioms_UInt64Vec.size());

    // Compile
    auto processAxioms = [&]() noexcept -> void
    {
        for(std::vector<uint64_t>& Axiom_i : Axioms_UInt64Vec) 
        {
            uint64_t  lhs = Axiom_i[0];
            uint64_t  rhs = Axiom_i[1];
    
            uint64_t _lhs = Axiom_i[0];
            uint64_t _rhs = Axiom_i[1];
    
            if (_lhs < _rhs)
            {
                lhs = _rhs;
                rhs = _lhs;
            }
            
            Axiom_Struct Axiom;
            Axiom_Struct Axiom2;
            
            Axiom.guid = GUID++;
            Axiom2.guid = GUID++;
            Axiom.PrimaryKey_UInt64 = lhs;
            Axiom2.PrimaryKey_UInt64 = rhs;
            Axiom.RHSCallGraph_UInt64Map[GUID - 1] = true;
            Axiom2.LHSCallGraph_UInt64Map[GUID - 2] = true;
            
            Axioms_Vec.push_back(Axiom);
            Axioms_Vec.push_back(Axiom);
            
            if(Theorem.SubkeyFOUND_LHS(lhs))
            {
                Axiom.LHS
            }
            
            if(Theorem.SubkeyFOUND_RHS(lhs))
            {
                
            }
            
            if(Theorem.SubkeyFOUND_LHS(rhs))
            {
                
            }
            
            if(Theorem.SubkeyFOUND_RHS(rhs))
            {
                
            }
        }
        
        uint64_t i{};
        for(std::vector<uint64_t>& Axiom_i : Axioms_UInt64Vec) 
        {
            std::unordered_map<uint64_t, bool> _cg1;
            std::unordered_map<uint64_t, bool> _cg2;
            
            LHSReduceCallGraph_UInt64Map.insert(std::make_pair(i, _cg1));
            RHSExpandCallGraph_UInt64Map.insert(std::make_pair(i, _cg2));

            uint64_t j{};
            for(std::vector<uint64_t>& Axiom_j : Axioms_UInt64Vec) 
            {
                bool ijAvoidsACallLoop_Flag = (i != j); // Avoid Call loops
                
                if (ijAvoidsACallLoop_Flag)
                {
					const bool bSubnetFound_Flag_lhsReduce = ((Axiom_i.at(0) % Axiom_j.at(0)) == 0); // "1 + 1" ==> "2" ?
					const bool bSubnetFound_Flag_lhsExpand = ((Axiom_i.at(0) % Axiom_j.at(1)) == 0); // "2" ==> "1 + 1" ?
					const bool bSubnetFound_Flag_rhsReduce = ((Axiom_i.at(1) % Axiom_j.at(0)) == 0); // "2" <== "1 + 1" ?
					const bool bSubnetFound_Flag_rhsExpand = ((Axiom_i.at(1) % Axiom_j.at(1)) == 0); // "1 + 1" <== "2" ?
					
                    if (bSubnetFound_Flag_lhsReduce)
                    {
                        LHSReduceCallGraph_UInt64Map[i][j] = true;
                    }
        
                    if (bSubnetFound_Flag_lhsExpand)
                    {
                        LHSExpandCallGraph_UInt64Map[i][j] = true;
                    }
        
                    if (bSubnetFound_Flag_rhsReduce)
                    {
                        RHSReduceCallGraph_UInt64Map[i][j] = true;
                    }
        
                    if (bSubnetFound_Flag_rhsExpand)
                    {
                        RHSExpandCallGraph_UInt64Map[i][j] = true;
                    }
                }
                j++;
            }
            i++;
        }
    };
    
    processAxioms();
	
	const auto end_time_chrono = std::chrono::high_resolution_clock::now();
	const auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
	std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;

    // Iterate and print the contents of the map
    for (const auto& outer_pair : LHSReduceCallGraph_UInt64Map) {
        uint64_t outer_key = outer_pair.first;
        const std::unordered_map<uint64_t, bool>& inner_map = outer_pair.second;

        for (const auto& inner_pair : inner_map) {
            uint64_t inner_key = inner_pair.first;
            bool value = inner_pair.second;

            std::cout << "LHSReduceCallGraph_UInt64Map[" << outer_key << "][" << inner_key << "] = " << std::boolalpha << value << '\n';
        }
    }

    // Iterate and print the contents of the map
    for (const auto& outer_pair : LHSExpandCallGraph_UInt64Map) {
        uint64_t outer_key = outer_pair.first;
        const std::unordered_map<uint64_t, bool>& inner_map = outer_pair.second;

        for (const auto& inner_pair : inner_map) {
            uint64_t inner_key = inner_pair.first;
            bool value = inner_pair.second;

            std::cout << "LHSExpandCallGraph_UInt64Map[" << outer_key << "][" << inner_key << "] = " << std::boolalpha << value << '\n';
        }
    }

    // Iterate and print the contents of the map
    for (const auto& outer_pair : RHSReduceCallGraph_UInt64Map) {
        uint64_t outer_key = outer_pair.first;
        const std::unordered_map<uint64_t, bool>& inner_map = outer_pair.second;

        for (const auto& inner_pair : inner_map) {
            uint64_t inner_key = inner_pair.first;
            bool value = inner_pair.second;

            std::cout << "RHSReduceCallGraph_UInt64Map[" << outer_key << "][" << inner_key << "] = " << std::boolalpha << value << '\n';
        }
    }

    // Iterate and print the contents of the map
    for (const auto& outer_pair : RHSExpandCallGraph_UInt64Map) {
        uint64_t outer_key = outer_pair.first;
        const std::unordered_map<uint64_t, bool>& inner_map = outer_pair.second;

        for (const auto& inner_pair : inner_map) {
            uint64_t inner_key = inner_pair.first;
            bool value = inner_pair.second;

            std::cout << "RHSExpandCallGraph_UInt64Map[" << outer_key << "][" << inner_key << "] = " << std::boolalpha << value << '\n';
        }
    }
    
    return 0;
}
