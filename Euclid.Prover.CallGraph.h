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

int main()
{
	const auto start_time_op = std::chrono::high_resolution_clock::now();

    std::function<void(uint64_t&,std::vector<uint64_t>&)> Reduce = [](uint64_t& OutPrimaryKey_UInt64Ref, std::vector<uint64_t>& OutProofStack_UInt64VecRef) noexcept -> void {
        
    };
    
    std::function<void(uint64_t&,std::vector<uint64_t>&)> Expand = [](uint64_t& OutPrimaryKey_UInt64Ref, std::vector<uint64_t>& OutProofStack_UInt64VecRef) noexcept -> void {
        
    };
    enum class Indirection : uint64_t
	{
		_auto,
		_reduce,
		_expand
	};
    struct AxiomProtoStruct
    {
        const uint64_t LHSPrimaryKey_ConstUInt64;
        const uint64_t RHSPrimaryKey_ConstUInt64;
        std::vector<uint64_t> ProofStack_VecUInt64;
        std::unordered_map<uint64_t,bool> ReduceCallGraph_Map;
        std::unordered_map<uint64_t,bool> ExpanCallGraph_Map;
        std::unordered_map<uint64_t,bool> CallHistory_Map;
    };
    struct ProofStruct : public AxiomProtoStruct
    {
        Indirection Indir_EnumClass = Indirection::_auto;
    };
    struct AxiomStruct : public AxiomProtoStruct
    {
        
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
	std::vector<std::vector<uint64_t>> Axioms_UInt64Vec =
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
			5 // 4 == 5
		}
	};
	std::unordered_map<uint64_t, std::vector<uint64_t>> LHSPrimaryKeyHistory_VecMap;
	std::unordered_map<uint64_t, std::vector<uint64_t>> RHSPrimaryKeyHistory_VecMap;
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> LHSCallHistory_Map;
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> RHSCallHistory_Map;
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> LHSCallGraph_UInt64Map;
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> RHSCallGraph_UInt64Map;
	
	std::mutex mtx;

    auto processAxioms = [&]() 
    {
        std::atomic<uint64_t> i(0);
        std::for_each(std::execution::unseq, Axioms_UInt64Vec.begin(), Axioms_UInt64Vec.end(),
            [&](std::vector<uint64_t>& Axiom_i) 
            {
                { // local scope
                    const uint64_t _lhs = Axiom_i.at(0);
                    const uint64_t _rhs = Axiom_i.at(1);
                    if (_lhs < _rhs)
                    {
                        const uint64_t lhs = _rhs;
                        const uint64_t rhs = _lhs;
                        Axiom_i.emplace<uint64_t>(Axiom_i.begin() + 0, uint64_t{ lhs });
                        Axiom_i.emplace<uint64_t>(Axiom_i.begin() + 1, uint64_t{ rhs });
                    }
                }

                std::unordered_map<uint64_t, bool> _cgl; // Build lhs call graph
                std::unordered_map<uint64_t, bool> _cgr; // Build rhs call graph
                std::unordered_map<uint64_t, bool> _cg2l; // Build lhs call history map
                std::unordered_map<uint64_t, bool> _cg2r; // Build rhs call history map
                {
                    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
                    LHSCallGraph_UInt64Map.insert(std::make_pair(i.load(), _cgl));
                    RHSCallGraph_UInt64Map.insert(std::make_pair(i.load(), _cgr));
                    LHSCallHistory_Map.insert(std::make_pair(i.load(), _cg2l));
                    RHSCallHistory_Map.insert(std::make_pair(i.load(), _cg2r));
                }

                std::atomic<uint64_t> j(0);
                std::for_each(std::execution::par, Axioms_UInt64Vec.begin(), Axioms_UInt64Vec.end(),
                    [&](const std::vector<uint64_t>& Axiom_j) 
                    {
                        bool ijDoesNotCreateACallLoop_Flag = (i.load() != j.load()); // Avoid Call loops
                        if (ijDoesNotCreateACallLoop_Flag)
                        {
                            const uint64_t Subnet_UInt64_lhs = Axiom_i.at(0) / Axiom_j.at(1);
                            const uint64_t Subnet_UInt64_rhs = Axiom_i.at(1) / Axiom_j.at(0);
                            const bool bSubnetFound_Flag_lhs = (Subnet_UInt64_lhs % 1 == 0); // 2 == 1 + 1 ?
                            const bool bSubnetFound_Flag_rhs = (Subnet_UInt64_rhs % 1 == 0); // 1 + 1 == 2 ?
        
                            if (bSubnetFound_Flag_lhs)
                            {
                                std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
                                auto it = LHSCallGraph_UInt64Map.find(i.load());
                                if (it != LHSCallGraph_UInt64Map.end())
                                {
                                    it->second.insert(std::make_pair(j.load(), true));
                                }
                            }

                            if (bSubnetFound_Flag_rhs)
                            {
                                std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
                                auto it = RHSCallGraph_UInt64Map.find(j.load());
                                if (it != RHSCallGraph_UInt64Map.end())
                                {
                                    it->second.insert(std::make_pair(i.load(), true));
                                }
                            }
                        }
                        j.fetch_add(1);
                    });
                i.fetch_add(1);
            });
    };
    
    std::jthread ProcessAxiomsThread(processAxioms);
    ProcessAxiomsThread.join(); // Wait on thread to finish

	const auto end_time_op = std::chrono::high_resolution_clock::now();
	const auto duration_op = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_op - start_time_op).count();
	std::cout << "Total Duration (nanoseconds): " << duration_op << std::endl;

	return 0;

}




