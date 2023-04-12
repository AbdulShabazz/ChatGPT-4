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

	uint64_t guid{};
};

struct Theorem_Struct : public AxiomProto_Struct
{
	std::vector<uint64_t> ProofStack_VecUInt64;

	std::vector<std::string> ProofString_StdStrVec;

	Indirection_EnumClass Indir_EnumClass = Indirection_EnumClass::_auto;
};

struct Axiom_Struct : public AxiomProto_Struct
{

};

uint64_t GUID = 0;

bool ProofFound_Flag{};

uint64_t MaxAllowedProofs_UInt64 = 1;

std::atomic<uint64_t> BreadthFirstSearchDepth_UInt64{0};

void Reduce(Theorem_Struct InTheorem, Axiom_Struct InAxiom)
{
	/*
	if (localProofFound_Flag)
		cv.notify(ProofStack_VecUInt64)
	InTheorem.LHSCallGraph_UInt64Map[0][1]
	InTheorem.LHSPrimaryKey_UInt64 / InAxiom.LHSPrimaryKey_UInt64
	// safe increment or uint64_t add: a, b
	if (a > 0 && b > 0 && a > std::numeric_limits<uint64_t>::max() - b) {
		throw std::overflow_error("overflow");
	} 
	std::this_thread::sleep_for(std::chrono::nanoseconds(12));
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
	*/ 
	std::cout << "Invoke: Expand(...) : InAxiom.guid: " << InAxiom.guid << std::endl;
};

void Expand(Theorem_Struct InTheorem, Axiom_Struct InAxiom)
{
	/*
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
	*/
	std::cout << "Invoke: Expand(...) : InAxiom.guid: " << InAxiom.guid << std::endl;
};

void Auto(Theorem_Struct& InTheorem, std::vector<Axiom_Struct>& InAxioms_VecRef)
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

	std::thread ProcessTheoremThread(Auto, std::ref(Theorem), std::ref(Axioms_Vec));
	ProcessTheoremThread.join();

	const auto end_time_chrono = std::chrono::high_resolution_clock::now();
	const auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
	std::cout << "Total Duration (nanoseconds): " << duration_chrono << ", Axioms_Vec[0].guid: " << Axioms_Vec[0].guid << std::endl;

	return 0;

}

