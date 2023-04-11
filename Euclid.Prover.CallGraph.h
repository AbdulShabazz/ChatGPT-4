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
	const auto start_time_chrono = std::chrono::high_resolution_clock::now();

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
	
	std::unordered_map<uint64_t, std::vector<uint64_t>> LHSPrimaryKeyHistory_VecMap;
	std::unordered_map<uint64_t, std::vector<uint64_t>> RHSPrimaryKeyHistory_VecMap;
	
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> LHSCallHistory_UInt64Map;
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> RHSCallHistory_UInt64Map;
	
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> LHSCallGraph_UInt64Map;
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> RHSCallGraph_UInt64Map;

	auto processAxioms = [&]() noexcept -> void
	{
		uint64_t i{};
		for(std::vector<uint64_t>& Axiom_i : Axioms_UInt64Vec) 
		{
			std::unordered_map<uint64_t, bool> _cgl; // Build lhs call graph
			std::unordered_map<uint64_t, bool> _cgr; // Build rhs call graph
			std::unordered_map<uint64_t, bool> _cg2l; // Build lhs (empty) call history map
			std::unordered_map<uint64_t, bool> _cg2r; // Build rhs (empty) call history map
			{
				LHSCallGraph_UInt64Map.insert(std::make_pair(i, _cgl));
				RHSCallGraph_UInt64Map.insert(std::make_pair(i, _cgr));
				LHSCallHistory_UInt64Map.insert(std::make_pair(i, _cg2l));
				RHSCallHistory_UInt64Map.insert(std::make_pair(i, _cg2r));
			}

			uint64_t j{};
			for(std::vector<uint64_t>& Axiom_j : Axioms_UInt64Vec) 
			{
				bool ijDoesNotCreateACallLoop_Flag = (i != j); // Avoid Call loops
				
				if (ijDoesNotCreateACallLoop_Flag)
				{
					const uint64_t Subnet_UInt64_lhs = Axiom_i.at(0) / Axiom_j.at(1);
					const uint64_t Subnet_UInt64_rhs = Axiom_i.at(1) / Axiom_j.at(0);
					const bool bSubnetFound_Flag_lhs = (Subnet_UInt64_lhs % 1 == 0); // 2 == 1 + 1 ?
					const bool bSubnetFound_Flag_rhs = (Subnet_UInt64_rhs % 1 == 0); // 1 + 1 == 2 ?

					if (bSubnetFound_Flag_lhs)
					{
						auto it = LHSCallGraph_UInt64Map.find(i);
						
						if (it != LHSCallGraph_UInt64Map.end())
						{
							it->second.insert(std::make_pair(j, true));
						}
					}

					if (bSubnetFound_Flag_rhs)
					{
						auto it = RHSCallGraph_UInt64Map.find(j);
						
						if (it != RHSCallGraph_UInt64Map.end())
						{
							it->second.insert(std::make_pair(i, true));
						}
					}
				}
				j++;
			}
			i++;
		}
	};
	
	std::mutex mtx;
	
	const std::size_t num_threads = std::thread::hardware_concurrency() - 1; // Reserve the main thread
		
	std::jthread ProcessAxiomsThread(processAxioms);
	
	enum class Indirection_EnumClass : uint64_t
	{
		_auto,
		_reduce,
		_expand
	};
	
	struct AxiomProto_Struct
	{
		uint64_t TaskListIndex_UInt64{};
		uint64_t LHSPrimaryKey_UInt64{};
		uint64_t RHSPrimaryKey_UInt64{};
		
		std::vector<uint64_t> ProofStack_VecUInt64;
		
		std::vector<std::string> LHSAxiom_StdStrVec;
		std::vector<std::string> RHSAxiom_StdStrVec;
		
		std::unordered_map<uint64_t,bool> LHSCallGraph_UInt64Map;
		std::unordered_map<uint64_t,bool> RHSCallGraph_UInt64Map;
		std::unordered_map<uint64_t,bool> LHSCallHistory_UInt64Map;
		std::unordered_map<uint64_t,bool> RHSCallHistory_UInt64Map;
		
		bool bParseStrict_Flag = false;
		
		uint64_t guid{};
	};
	
	struct Theorem_Struct : public AxiomProto_Struct
	{
		std::vector<std::string> ProofString_StdStrVec;
		Indirection_EnumClass Indir_EnumClass = Indirection_EnumClass::_auto;
	};
	
	struct Axiom_Struct : public AxiomProto_Struct
	{
		
	};

	std::function<void(
		Theorem_Struct,
		Axiom_Struct,
		uint64_t,
		std::vector<uint64_t>)> 
	Reduce = [](
		Theorem_Struct InTheorem, 
		Axiom_Struct InAxiom, 
		uint64_t InPrimaryKey_UInt64Ref, 
		std::vector<uint64_t> OutProofStack_UInt64VecRef) noexcept -> void 
	{
		
	};

	std::function<void(
		Theorem_Struct,
		Axiom_Struct,
		uint64_t,
		std::vector<uint64_t>)>
	Expand = [](
		Theorem_Struct InTheorem, 
		Axiom_Struct InAxiom, 
		uint64_t InPrimaryKey_UInt64Ref, 
		std::vector<uint64_t> OutProofStack_UInt64VecRef) noexcept -> void 
	{
		
	};
	
	static uint64_t GUID = 0;
	
	Theorem_Struct Theorem;
	
	std::vector<Axiom_Struct> Axioms_Vec;
	Axioms_Vec.resize(Axioms_UInt64Vec.size());
	
	uint64_t nIdxUInt64 = 0;
	
	ProcessAxiomsThread.join(); // Wait on Axioms thread to finish
	
	for(const std::vector<uint64_t>& pKeyUInt64 : Axioms_UInt64Vec)
	{
		uint64_t  lhs = pKeyUInt64[0];
		uint64_t  rhs = pKeyUInt64[1];
		
		uint64_t _lhs = pKeyUInt64[0];
		uint64_t _rhs = pKeyUInt64[1];
		
		if (_lhs < _rhs)
		{
			 lhs = _rhs;
			 rhs = _lhs;
		}
		
		if(nIdxUInt64 > 0)
		{
			Axiom_Struct elem;
			
			elem.guid = GUID++;
			elem.LHSPrimaryKey_UInt64 = lhs;
			elem.RHSPrimaryKey_UInt64 = rhs;
			elem.LHSCallHistory_UInt64Map = LHSCallHistory_UInt64Map[nIdxUInt64];
			elem.RHSCallHistory_UInt64Map = RHSCallHistory_UInt64Map[nIdxUInt64];
			elem.LHSCallGraph_UInt64Map = LHSCallGraph_UInt64Map[nIdxUInt64];
			elem.RHSCallGraph_UInt64Map = RHSCallGraph_UInt64Map[nIdxUInt64];
			
			Axioms_Vec.emplace_back(elem);
		}
		
		else 
		{
			Theorem_Struct elem;
			
			elem.guid = GUID++;
			elem.LHSPrimaryKey_UInt64 = lhs;
			elem.RHSPrimaryKey_UInt64 = rhs;
			elem.LHSCallHistory_UInt64Map = LHSCallHistory_UInt64Map[nIdxUInt64];
			elem.RHSCallHistory_UInt64Map = RHSCallHistory_UInt64Map[nIdxUInt64];
			elem.LHSCallGraph_UInt64Map = LHSCallGraph_UInt64Map[nIdxUInt64];
			elem.RHSCallGraph_UInt64Map = RHSCallGraph_UInt64Map[nIdxUInt64];
			   
		}
			
		nIdxUInt64++;
	}

	const auto end_time_chrono = std::chrono::high_resolution_clock::now();
	const auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
	std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;

	return 0;

}
