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

uint64_t GUID = 0;

std::atomic<uint64_t> recursive_calls_available(2048);

{ // local scope: Get the current stack size limit
	struct rlimit stack_limit;
	if (getrlimit(RLIMIT_STACK, &stack_limit) == 0)
	{
		recursive_calls_available.store(stack_limit.rlim_cur, std::memory_order_relaxed); 
	}
}

enum class Indirection_EnumClass : uint64_t
{
	_auto,
	_reduce,
	_expand
};

struct AxiomProto_Struct
{
	uint64_t LHSPrimaryKey_UInt64{};
	uint64_t RHSPrimaryKey_UInt64{};
	
	std::vector<std::string> LHSAxiom_StdStrVec;
	std::vector<std::string> RHSAxiom_StdStrVec;
	
	std::unordered_map<uint64_t,bool> LHSExpandCallGraph_UInt64Map;
	std::unordered_map<uint64_t,bool> LHSReduceCallGraph_UInt64Map;
	std::unordered_map<uint64_t,bool> RHSExpandCallGraph_UInt64Map;
	std::unordered_map<uint64_t,bool> RHSReduceCallGraph_UInt64Map;
	
	std::unordered_map<uint64_t,bool> LHSExpandCallHistory_UInt64Map;
	std::unordered_map<uint64_t,bool> LHSReduceCallHistory_UInt64Map;
	std::unordered_map<uint64_t,bool> RHSExpandCallHistory_UInt64Map;
	std::unordered_map<uint64_t,bool> RHSReduceCallHistory_UInt64Map;
	
	bool bParseStrict_Flag = false;
	
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
};

struct Axiom_Struct : public AxiomProto_Struct
{
	
};

__attribute__((always_inline))
void Reduce(Theorem_Struct InTheorem, const Axiom_Struct& InAxiom)
{
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
		InTheorem.TotalProofsFound_UInt64++;
		InTheorem.ProofFound_Flag = true;
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

__attribute__((always_inline))
void Expand(Theorem_Struct InTheorem, const Axiom_Struct& InAxiom)
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

void Auto(Theorem_Struct& InTheorem, const std::vector<Axiom_Struct>& InAxioms_VecRef)
{/*
	switch(InTheorem.Indir_EnumClass)
	{
		case Indirection_EnumClass::_reduce:
		{
			for(Axiom_Struct& Axiom : InAxioms_VecRef)
			{
				Reduce(InTheorem, Axiom);
			}
			break;   
		}
		
		case Indirection_EnumClass::_expand:
		{
			for(Axiom_Struct& Axiom : InAxioms_VecRef)
			{
				Expand(InTheorem, Axiom);
			}
			break;
		}
		
		case Indirection_EnumClass::_auto:
		default:
		{
			for(Axiom_Struct& Axiom : InAxioms_VecRef)
			{
				Reduce(InTheorem, Axiom);
				Expand(InTheorem, Axiom);
			}
			break;
		}
	} */
	std::cout << "Invoke: Auto(...) : InAxioms_VecRef[0].guid: " << InAxioms_VecRef[0].guid << std::endl;
};

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

	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> LHSReduceCallGraph_UInt64Map;
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> LHSExpandCallGraph_UInt64Map;
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> RHSReduceCallGraph_UInt64Map;
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, bool>> RHSExpandCallGraph_UInt64Map;

	// Compile
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
				LHSExpandCallGraph_UInt64Map.insert(std::make_pair(i, _cgl));
				LHSReduceCallGraph_UInt64Map.insert(std::make_pair(i, _cgl));
				RHSExpandCallGraph_UInt64Map.insert(std::make_pair(i, _cgr));
				RHSReduceCallGraph_UInt64Map.insert(std::make_pair(i, _cgr));
			}

			uint64_t j{};
			for(std::vector<uint64_t>& Axiom_j : Axioms_UInt64Vec) 
			{
				bool ijDoesNotCreateACallLoop_Flag = (i != j); // Avoid Call loops
				
				if (ijDoesNotCreateACallLoop_Flag)
				{
					const uint64_t Subnet_UInt64_lhsReduce = Axiom_i.at(0) % Axiom_j.at(0);
					const uint64_t Subnet_UInt64_lhsExpand = Axiom_i.at(0) % Axiom_j.at(1);
					const uint64_t Subnet_UInt64_rhsReduce = Axiom_i.at(1) % Axiom_j.at(0);
					const uint64_t Subnet_UInt64_rhsExpand = Axiom_i.at(1) % Axiom_j.at(1);
					
					const bool bSubnetFound_Flag_lhsReduce = (Subnet_UInt64_lhsReduce == 0); // 1 + 1 ==> 2 ?
					const bool bSubnetFound_Flag_lhsExpand = (Subnet_UInt64_lhsExpand == 0); // 2 ==> 1 + 1 ?
					const bool bSubnetFound_Flag_rhsReduce = (Subnet_UInt64_rhsReduce == 0); // 2 <== 1 + 1 ?
					const bool bSubnetFound_Flag_rhsExpand = (Subnet_UInt64_rhsExpand == 0); // 1 + 1 <== 2 ?

					if (bSubnetFound_Flag_lhsReduce)
					{
						auto it = LHSReduceCallGraph_UInt64Map.find(i);
						
						if (it != LHSReduceCallGraph_UInt64Map.end())
						{
							it->second.insert(std::make_pair(j, true));
						}
					}

					if (bSubnetFound_Flag_lhsExpand)
					{
						auto it = LHSExpandCallGraph_UInt64Map.find(i);
						
						if (it != LHSExpandCallGraph_UInt64Map.end())
						{
							it->second.insert(std::make_pair(j, true));
						}
					}

					if (bSubnetFound_Flag_rhsReduce)
					{
						auto it = RHSReduceCallGraph_UInt64Map.find(i);
						
						if (it != RHSReduceCallGraph_UInt64Map.end())
						{
							it->second.insert(std::make_pair(j, true));
						}
					}

					if (bSubnetFound_Flag_rhsExpand)
					{
						auto it = RHSExpandCallGraph_UInt64Map.find(i);
						
						if (it != RHSExpandCallGraph_UInt64Map.end())
						{
							it->second.insert(std::make_pair(j, true));
						}
					}
				}
				j++;
			}
			i++;
		}
	};

	std::thread ProcessAxiomsThread(processAxioms);

	Theorem_Struct Theorem;

	std::vector<Axiom_Struct> Axioms_Vec;
	Axioms_Vec.resize(Axioms_UInt64Vec.size());

	uint64_t nIdxUInt64 = 0;

	ProcessAxiomsThread.join(); // Wait on Axioms thread to finish

	// Build
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
			elem.LHSExpandCallGraph_UInt64Map = LHSExpandCallGraph_UInt64Map[nIdxUInt64];
			elem.LHSReduceCallGraph_UInt64Map = LHSReduceCallGraph_UInt64Map[nIdxUInt64];
			elem.RHSExpandCallGraph_UInt64Map = RHSExpandCallGraph_UInt64Map[nIdxUInt64];
			elem.RHSReduceCallGraph_UInt64Map = RHSReduceCallGraph_UInt64Map[nIdxUInt64];

			Axioms_Vec.at(nIdxUInt64-1) = elem;
		}

		else
		{
			Theorem_Struct elem;

			elem.guid = GUID++;
			elem.LHSPrimaryKey_UInt64 = lhs;
			elem.RHSPrimaryKey_UInt64 = rhs;
			elem.LHSExpandCallGraph_UInt64Map = LHSExpandCallGraph_UInt64Map[nIdxUInt64];
			elem.LHSReduceCallGraph_UInt64Map = LHSReduceCallGraph_UInt64Map[nIdxUInt64];
			elem.RHSExpandCallGraph_UInt64Map = RHSExpandCallGraph_UInt64Map[nIdxUInt64];
			elem.RHSReduceCallGraph_UInt64Map = RHSReduceCallGraph_UInt64Map[nIdxUInt64];
		}

		nIdxUInt64++;
	}

	std::mutex mtx;

	const std::size_t num_threads = std::thread::hardware_concurrency() - 1; // Reserve the main thread

	std::thread ProcessTheoremThread(Auto, std::ref(Theorem), std::cref(Axioms_Vec));
	ProcessTheoremThread.join();
	
	const auto end_time_chrono = std::chrono::high_resolution_clock::now();
	const auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
	std::cout << "Total Duration (nanoseconds): " << duration_chrono << ", Axioms_Vec[0].guid: " << Axioms_Vec[0].guid << std::endl;

	return 0;

}
