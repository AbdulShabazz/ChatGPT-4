# Proposal for including std::reduction_map and std::reduction_multimap in the C++23 Standard

## Abstract
We propose the addition of two new containers to the C++ Standard Template Library (STL): `std::reduction_map` and `std::reduction_multimap`. These containers are similar to `std::map` and `std::multimap`, but they include an additional component known as an `arbitrator function` that can transform different keys into a single, 'base' or 'canonical' form. This proposal aims to provide a general-purpose solution to map multiple keys to a single value or multiple values based on the principle of semantic equivalence.

## Description
### std::reduction_map
`std::reduction_map` is a type of associative container that stores elements formed by the combination of a key value and a mapped value. It is similar to `std::map`, but it uses an arbitrator function that can parse reduction_map keys for their semantic equivalence. In the absence of an arbitrator function, it defaults to the behavior of C++ `std::map`.

The signature for `std::reduction_map` could be:

```
template<
    typename Key, // map::key_type //
    typename T, // map::mapped_type //
    typename ArbitratorFunc = std::function<Key(const Key&)>, // arbitrator function //
    typename Compare = std::less<Key>, // map::key_compare //
    typename Alloc = std::allocator<std::pair<const Key, T>> // map::allocator_type //
> 
class reduction_map { /* ... */ };
```
The `ArbitratorFunc` is a new key-mapping function component that accepts a key as input and returns a 'base' or 'canonical' form of the key.

### std::reduction_multimap
`std::reduction_multimap` is similar to `std::reduction_map`, but its keys do not have to be unique, so it can have multiple pairs with equivalent keys. This makes it useful for representing many-to-many relationships. If no arbitrator function is provided, `std::reduction_multimap` defaults to the behavior of `std::multimap`!

The signature for `std::reduction_multimap` could be:

```
template<
    typename Key, // map::key_type //
    typename T, // map::mapped_type //
    typename ArbitratorFunc = std::function<Key(const Key&)>, // arbitrator function //
    typename Compare = std::less<Key>, // map::key_compare //
    typename Alloc = std::allocator<std::pair<const Key, T>> // map::allocator_type //
> 
class reduction_multimap { /* ... */ };
```

## Use Cases

For a real world use-case example, ontology mapping is a crucial aspect in many fields including Artificial Intelligence (AI), Natural Language Processing (NLP), and particularly in the development of large language models. Ontology mapping refers to the process of relating similar concepts from different ontologies, which is often necessary when integrating different data sources, developing interoperability between AI systems, or creating semantic web services.

In the context of large language model development, an important task is the semantic understanding and representation of words, phrases, or concepts. Often, there is a need to map different lexical or syntactical forms of a concept to the same semantic entity. This is where our proposed `std::reduction_map` and `std::reduction_multimap` can be particularly useful.

Let's consider an example use case:

Imagine we're developing a language model that has to understand and answer questions about mathematics. The model should be able to understand that the phrases "1", "one plus zero", "zero plus one", "1 + 0", and "0 + 1" all refer to the same concept, i.e., they all have the same result "1".

In this case, we could define our `std::reduction_map` with `std::string` as the key and an object representing the mathematical concept as the value. The ArbitratorFunc would be a function that can parse and simplify mathematical expressions. Therefore, all the different forms that represent the same concept would be mapped to the same object:

```
std::reduction_map<std::string, Euclid_Prover, MathExpressionSimplifier> math_concepts;
math_concepts["1"] = "One";
math_concepts["1 + 0"]; // returns "One"; //
math_concepts["0 + 1"]; // returns "One"; //
math_concepts["one plus zero"]; // returns "One"; //
math_concepts["zero plus one"]; // returns "One"; //
```

After these insertions, the model would know that "1 + 0", "0 + 1", "one plus zero", and "zero plus one" all refer to the same concept, and it can treat them as semantically equivalent. It's clear how this can vastly simplify the process of mapping varied representations of a concept to a single semantic entity.

An example of an arbitrator function for this could be one such as the following, which maps the tokens { "0", "1", "zero", "one", "plus", "+" } to primes - whose presence in keys are then multiplied together to quickly get a unique prime composite which can be checked via modular arithmetic for a token's presence in the key:

```
#include <thread>
#include <initializer_list>
#include <queue>
#include <unordered_map>
#include <future>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include <boost/multiprecision/cpp_int.hpp> 

namespace Euclid_Prover
{
	using BigInt128_t = boost::multiprecision::cpp_int;

	std::unordered_multimap<
		std::string, BigInt128_t>
		SymbolToPrime_UInt64MultiMap =
	{
		{"=", 2},
		{"{", 3},
		{"}", 5},
		{"(", 7},
		{")", 11},
		{"[", 13},
		{"]", 17}
	};

	std::size_t PrimeCompositeVecSize_UInt64{ 7 };

	std::vector<BigInt128_t> PrimeComposite_UInt64Vec{ 2, 3, 5, 7, 11, 13, 17 };

	std::vector<
		std::vector<
		std::vector<
		std::string>>> TempProofSteps{};

	/**
	 * Prime() : Return the next prime in the series...
	 * usage: Prime(); // returns 23
	*/
	BigInt128_t Prime()
	{
		__stdtracein__("Euclid_Prover::Prime");
		const std::size_t Index_UInt64 = PrimeCompositeVecSize_UInt64++;
		for (BigInt128_t i = PrimeComposite_UInt64Vec.back() + 2; PrimeComposite_UInt64Vec.size() < PrimeCompositeVecSize_UInt64; i += 2)
		{
			bool Add_Flag{ true };

			BigInt128_t j{};

			const BigInt128_t J = i / 4;

			for (const BigInt128_t& val : PrimeComposite_UInt64Vec)
			{

				if (( i % val ) == 0)
				{
					Add_Flag = false;
					break;
				}

				if (++j >= J)
				{
					break;
				}
			}

			if (Add_Flag)
			{
				PrimeComposite_UInt64Vec.emplace_back(i);
			}
		}
		__stdtraceout__("Euclid_Prover::Prime");
		return PrimeComposite_UInt64Vec[Index_UInt64];
	}

	// Generate Internal Route Map //
	int __Prove__
	(
		const
		std::vector<
		std::vector<
		std::string>>&
		InTheoremStdStrVec,

		const
		std::vector<
		std::vector<
		std::vector<
		std::string>>>&
		InAxiomsStdStrVec,

		bool&
		OutProofFound_FlagRef,

		bool&
		OutStatusReadyFlag,

		std::vector<
		std::vector<
		std::vector<
		std::string>>>&
		OutProofStepStdStrVecRef,

		std::vector<
		std::vector<
		std::string>>&
		OutAxiomCommitLogStdStrVecRef
	)
	{
		__stdtracein__("STDThreadProve");

		TempProofSteps = {};

		bool QED{};

		BigInt128_t GUID_UInt64{};

		std::vector<BigInt128_t> Theorem_UInt64Vec;

		auto PopulateTheoremVec =
			[
				&
			]
		( ) -> void
		{
			__stdtracein__("PopulateTheoremVec");
			for (const std::vector<std::string>& Subnet_StdStrVec : InTheoremStdStrVec)
			{
				BigInt128_t PrimeProduct_UInt64Vec{ 1 };
				for (const std::string& Symbol_StdStr : Subnet_StdStrVec)
				{
					__stdlog__({ "'",Symbol_StdStr,"' " });
					const auto& it = SymbolToPrime_UInt64MultiMap.find(Symbol_StdStr);
					if (it != SymbolToPrime_UInt64MultiMap.end())
					{
						PrimeProduct_UInt64Vec *= it->second;
						__stdlog__({ "Prime: ", Symbol_StdStr ," <- ",it->second.str(),", PrimeProduct: ", PrimeProduct_UInt64Vec.str() });
					} else {
						// This key/value pair is not in the prime number multimap... //
						const BigInt128_t p = Prime();
						SymbolToPrime_UInt64MultiMap.emplace(Symbol_StdStr, p);
						PrimeProduct_UInt64Vec *= p;
						__stdlog__({ "New Prime: ", Symbol_StdStr ," <- ",p.str(),", PrimeProduct: ", PrimeProduct_UInt64Vec.str() });
					}
				}
				__stdlog__({ "" });
				Theorem_UInt64Vec.emplace_back(PrimeProduct_UInt64Vec);
			}
			Theorem_UInt64Vec.emplace_back(0); // guid //
			Theorem_UInt64Vec.emplace_back(0); // last_UInt64 {"_root"} //
			__stdtraceout__("PopulateTheoremVec");
		};

		std::vector<
			std::vector<
			BigInt128_t>> Axioms_UInt64Vec;

		auto PopulateAxiomVec =
			[
				&
			]
		( ) -> void
		{
			__stdtracein__("PopulateAxiomVec");
			for
				(
					const
					std::vector<
					std::vector<
					std::string>>&Subnet_StdStrVec :
					InAxiomsStdStrVec
				)
			{
				std::vector<BigInt128_t> TempInnerAxiom_UInt64Vec{};
				for
					(
						const
						std::vector<
						std::string>& Expression_StdStrVec :
						Subnet_StdStrVec
					)
				{
					BigInt128_t PrimeProduct_UInt64Vec{ 1 };
					for (const std::string& Symbol_StdStr : Expression_StdStrVec)
					{
						__stdlog__({ "'",Symbol_StdStr,"' " });
						const auto& it = SymbolToPrime_UInt64MultiMap.find(Symbol_StdStr);
						if (it != SymbolToPrime_UInt64MultiMap.end())
						{
							PrimeProduct_UInt64Vec *= it->second;
							__stdlog__({ "Prime: ", Symbol_StdStr ," <- ",it->second.str(),", PrimeProduct: ", PrimeProduct_UInt64Vec.str() });
						} else {
							// This key/value pair is not in the prime number multimap... //
							const BigInt128_t p = Prime();
							SymbolToPrime_UInt64MultiMap.emplace(Symbol_StdStr, p);
							PrimeProduct_UInt64Vec *= p;
							__stdlog__({ "New Prime: ", Symbol_StdStr ," <- ",p.str(),", PrimeProduct: ", PrimeProduct_UInt64Vec.str() });
						}
					}
					__stdlog__({ "" });
					TempInnerAxiom_UInt64Vec.emplace_back(PrimeProduct_UInt64Vec);
				}
				TempInnerAxiom_UInt64Vec.emplace_back(++GUID_UInt64); // guid
				Axioms_UInt64Vec.emplace_back(TempInnerAxiom_UInt64Vec);
			}
			__stdtraceout__("PopulateAxiomVec");
		};

		std::unordered_map<BigInt128_t, std::unordered_map<BigInt128_t, bool>> CallGraphUInt64Map{};

		constexpr int LHS = 0;
		constexpr int RHS = 1;
		constexpr int guid_UInt64 = 2;
		constexpr int last_UInt64 = 3;
		constexpr int ProofStackUInt64 = 4;

		auto RebalanceTheoremVec =
			[
				&
			]
		( ) -> void
		{
			__stdtracein__("RebalanceTheoremVec");
			BigInt128_t& lhs = Theorem_UInt64Vec[LHS];
			BigInt128_t& rhs = Theorem_UInt64Vec[RHS];

			if (lhs < rhs)
			{
				std::swap(lhs, rhs);
			}
			__stdtraceout__("RebalanceTheoremVec");
		};

		auto RebalanceAxiomVec =
			[
				&
			]
		( ) -> void
		{
			__stdtracein__("RebalanceAxiomVec");
			for (std::vector<BigInt128_t>& Axiom_i : Axioms_UInt64Vec)
			{
				BigInt128_t& lhs = Axiom_i[LHS];
				BigInt128_t& rhs = Axiom_i[RHS];

				if (lhs < rhs)
				{
					std::swap(lhs, rhs);
				}
			}
			__stdtraceout__("RebalanceAxiomVec");
		};

		PopulateTheoremVec();
		PopulateAxiomVec();

		RebalanceTheoremVec();
		RebalanceAxiomVec();

		std::size_t MaxAllowedProofs_UInt64{ 1 };
		std::size_t TotalProofsFound_UInt64{};

		using InternalProofStackUInt64Vec = std::vector<BigInt128_t>;
		std::unordered_map<BigInt128_t, InternalProofStackUInt64Vec> LHSRouteHistoryMap, RHSRouteHistoryMap;

		//std::unordered_map<BigInt128_t, bool> TimeoutEntropyQueue{}; // Measure the change in entropy in the Task_Thread //

		bool bTimeoutFlag{};

		std::priority_queue<
			std::vector<
			BigInt128_t>> Tasks_Thread, FastForwardTask_Thread;

		Tasks_Thread.push(Theorem_UInt64Vec);

		// *** Core Proof Engine (Loop) *** //

		bool bFastForwardFlag{};

		while (!Tasks_Thread.empty() && !QED && !bTimeoutFlag)
		{

			const std::vector<BigInt128_t>
				Theorem{ !bFastForwardFlag ? Tasks_Thread.top() : FastForwardTask_Thread.top() };

			!bFastForwardFlag ? Tasks_Thread.pop() : FastForwardTask_Thread.pop();

			bFastForwardFlag = false;

			// Check rewrite proofs in the task queue //
			const bool TentativeProofFound_Flag = ( Theorem[LHS] == Theorem[RHS] );

			if (TentativeProofFound_Flag)
			{
				/**
				Alright, we have successfully employed prime number fields
				to effectively and swiftly reduce the size of our potential solution set.

				Now, our next step is to confirm that this narrowed down solution space
				indeed leads us to a valid routing map...
				*/

				__stdlog__({ "Tentative Proof Found" });
				__stdlog__({ "Theorem {", Theorem[LHS].str(), ", ", Theorem[RHS].str(), "} " });

				bool ProofFoundFlag{ true };

				TempProofSteps.emplace_back(InTheoremStdStrVec);

				auto Rewrite = [&]
					(
						auto& th,
						const auto& from,
						const auto& to
					) -> bool
				{
					__stdtracein__("Rewrite");
					bool bSuccessFlag{};

					if (th.size() < from.size())
						return false;

					std::unordered_map<std::string, std::string>

						endscope{ {"(", ")"}, { "{", "}" }, { "[", "]" } };

					std::vector<std::string> result{};

					std::size_t i{};

					const std::size_t I{ from.size() };

					for (const auto& val : th)
					{
						__stdlog__({ "Next val: ", val });

						if (!bSuccessFlag && val == from[i])
						{
							++i;

							__stdlog__({ "Match found: ", val, " >> " }, false);

							const bool bLocalSubnetFoundFlag = ( i == I );

							if (bLocalSubnetFoundFlag)
							{
								for (const auto& u2 : to)
								{
									__stdlog__({ u2, " " }, false);
									result.emplace_back(u2);
								}

								bSuccessFlag = true;

								__stdlog__({ ">> Substitution made" });

								i = 0;

								continue;
							}
						} else {
							i = 0; // reset //

							__stdlog__({ "No Match found: ", val });

							result.emplace_back(val);
						}
						__stdlog__({ "" });
					}

					th = result;
					__stdtraceout__("Rewrite");
					return bSuccessFlag;
				};
				
				auto ProofVerified = [&]
					(
						const
						std::vector<
						BigInt128_t>&
						InTheoremUInt64,

						const
						std::vector<
						std::vector<
						std::string>>&
						InTheoremStdStrVec,

						const
						std::vector<
						std::vector<
						std::vector<
						std::string>>>&
						InAxiomsStdStrVec
					) -> bool
				{
					__stdtracein__("ProofVerified");

					bool ReturnStatusFlag{true};

					std::vector<
						std::vector<
						std::string>>
						TempTheoremStdStrVec{ InTheoremStdStrVec };

					std::vector<
						std::string>
						TempAxiomCommitLogStdStrVecRef;

					/**
					Loop through the Theorem's proofstack, which starts at Theorem[ProofStackUInt64],
					and read off a pair of values from the vector:

					1. An opcode whose hexadecimal value
					ranges from 0x00 to 0x03 (See above for further explanation)

					2. An index into InAxiomsStdStrVec, where guid is Axiom_[guid].
					*/

					std::size_t i { ProofStackUInt64 };

					OutProofStepStdStrVecRef.push_back(TempTheoremStdStrVec);

					while (i < InTheoremUInt64.size())
					{
						const std::size_t& opcode = std::size_t{ InTheoremUInt64[i++] };
						const std::size_t& guid = std::size_t{ InTheoremUInt64[i++] - 1 };

						switch (opcode)
						{
							case 0x00:
							{ // "lhsreduce" operation //
								__stdlog__({ "lhs_reduce via Axiom_", std::to_string(guid) });
								ReturnStatusFlag =
									Rewrite (TempTheoremStdStrVec[LHS], InAxiomsStdStrVec[guid][LHS], InAxiomsStdStrVec[guid][RHS]);
								TempAxiomCommitLogStdStrVecRef.emplace_back("lhs_reduce via Axiom_" + std::to_string(guid));
								break;
							}
							case 0x01:
							{ // "lhsexpand" operation //
								__stdlog__({ "lhs_expand via Axiom_", std::to_string(guid) });
								ReturnStatusFlag =
									Rewrite (TempTheoremStdStrVec[LHS], InAxiomsStdStrVec[guid][RHS], InAxiomsStdStrVec[guid][LHS]);
								TempAxiomCommitLogStdStrVecRef.emplace_back("lhs_expand via Axiom_" + std::to_string(guid));
								break;
							}
							case 0x02:
							{ // "rhsreduce" operation //
								__stdlog__({ "rhs_reduce via Axiom_", std::to_string(guid) });
								ReturnStatusFlag =
									Rewrite (TempTheoremStdStrVec[RHS], InAxiomsStdStrVec[guid][LHS], InAxiomsStdStrVec[guid][RHS]);
								TempAxiomCommitLogStdStrVecRef.emplace_back("rhs_reduce via Axiom_" + std::to_string(guid));
								break;
							}
							case 0x03:
							{ // "rhsexpand" operation //
								__stdlog__({ "rhs_expand via Axiom_", std::to_string(guid) });
								ReturnStatusFlag =
									Rewrite (TempTheoremStdStrVec[RHS], InAxiomsStdStrVec[guid][RHS], InAxiomsStdStrVec[guid][LHS]);
								TempAxiomCommitLogStdStrVecRef.emplace_back("rhs_expand via Axiom_" + std::to_string(guid));
								break;
							}
							default:
							{
								// Invalid opcode. //
								TempAxiomCommitLogStdStrVecRef.emplace_back("???? via Axiom_" + std::to_string(guid));
								break;
							}
						} // end switch(opcode)
						OutProofStepStdStrVecRef.push_back(TempTheoremStdStrVec);

						if (!ReturnStatusFlag) 
							break;
					}
					OutAxiomCommitLogStdStrVecRef.push_back(TempAxiomCommitLogStdStrVecRef);

					// If TentativeProofVerified is unable to finish the loop, return false. //
					__stdtraceout__("ProofVerified");
					return ReturnStatusFlag;
				};

				if 
					(
						ProofVerified
						(
							Theorem,
							InTheoremStdStrVec,
							InAxiomsStdStrVec
						)
					)
				{
					++TotalProofsFound_UInt64;

					__stdlog__({ "Proof Found" });
					__stdlog__({ "Theorem {", Theorem[LHS].str(), ", ", Theorem[RHS].str(), "}\n" });

					if (TotalProofsFound_UInt64 >= MaxAllowedProofs_UInt64)
					{
						QED = true;
						break;
					}
				} else {
					// Retain Partial-proof //
					continue;
				}

			} else {

				// Add new rewrites to the task queue //
				const auto& theoremLHS = Theorem[LHS];
				const auto& theoremRHS = Theorem[RHS];

				//std::shared_mutex lhsMutex, rhsMutex, tasksMutex, ffMutex; //

				for (const auto& Axiom : Axioms_UInt64Vec)
				{
					const auto& AxiomLHS = Axiom[LHS];
					const auto& AxiomRHS = Axiom[RHS];

					//const bool SubnetFound = CallGraphUInt64Map[Theorem[last_UInt64]][Axiom[guid_UInt64]]; //
					//std::cout << SubnetFound << std::endl; //

					if (theoremLHS % AxiomLHS == 0 )
					{
						std::vector<BigInt128_t> Theorem_0000{ Theorem };
						Theorem_0000[LHS] = Theorem_0000[LHS] / AxiomLHS * AxiomRHS;

						Theorem_0000[last_UInt64] = Axiom[guid_UInt64];
						Theorem_0000.emplace_back(0x00); // Push opcode 0x00 onto the proofstack because we performed a _lhs _reduce operation) //
						Theorem_0000.emplace_back(Axiom[guid_UInt64]); // Push the Axiom ID onto the proofstack //
						__stdlog__({ "lhs_reduce in Module_0000 via Axiom_", Axiom[guid_UInt64].str(), " {", Theorem_0000[LHS].str(), ", ", Theorem_0000[RHS].str(), "}" });

						// Commit for later fast-forward //
						if (LHSRouteHistoryMap.find(Theorem_0000[LHS]) == LHSRouteHistoryMap.end())
							LHSRouteHistoryMap.emplace(Theorem_0000[LHS], Theorem_0000);

						// Attempt fast-forward //
						if (RHSRouteHistoryMap.find(Theorem_0000[LHS]) != RHSRouteHistoryMap.end()) {
							//std::cout << "Proof found in Module_0000 via Fast-Forward (FF)" << " {" << Theorem_0000[LHS].str() << ", " << Theorem_0000[LHS].str() << "}" << std::endl; //
							__stdlog__({ "Proof found in Module_0000 via Fast-Forward (FF)" });
							auto opcode = RHSRouteHistoryMap[Theorem_0000[LHS]].begin() + ProofStackUInt64;
							const auto OPCODE = RHSRouteHistoryMap[Theorem_0000[LHS]].end();
							for (; opcode != OPCODE; ++opcode)
								Theorem_0000.emplace_back(*opcode);
							Theorem_0000[RHS] = Theorem_0000[LHS];

							// Is the FF queue still empty? //
							if (FastForwardTask_Thread.empty()) {
								bFastForwardFlag = true;
								FastForwardTask_Thread.push(Theorem_0000);
								break;
							}
						}
						Tasks_Thread.push(Theorem_0000);
					}

					if (theoremLHS % AxiomRHS == 0)
					{
						std::vector<BigInt128_t> Theorem_0001{ Theorem };
						Theorem_0001[LHS] = Theorem_0001[LHS] / AxiomRHS * AxiomLHS;
						Theorem_0001[last_UInt64] = Axiom[guid_UInt64];
						Theorem_0001.emplace_back(0x01); // Push opcode 0x01 onto the proofstack because we performed a _lhs _expand operation) //
						Theorem_0001.emplace_back(Axiom[guid_UInt64]); // Push the Axiom ID onto the proofstack //
						__stdlog__({ "lhs_expand in Module_0001 via Axiom_", Axiom[guid_UInt64].str(), " {", Theorem_0001[LHS].str(), ", ", Theorem_0001[RHS].str(), "}" });

						// Commit for later fast-forward //
						if (LHSRouteHistoryMap.find(Theorem_0001[LHS]) == LHSRouteHistoryMap.end())
							LHSRouteHistoryMap.emplace(Theorem_0001[LHS], Theorem_0001);

						// Attempt fast-forward //
						if (RHSRouteHistoryMap.find(Theorem_0001[LHS]) != RHSRouteHistoryMap.end()) {
							//std::cout << "Proof found in Module_0001 via Fast-Forward (FF)" << " {" << Theorem_0001[LHS].str() << ", " << Theorem_0001[LHS].str() << "}" << std::endl; //
							__stdlog__({ "Proof found in Module_0001 via Fast-Forward (FF)" });
							auto opcode = RHSRouteHistoryMap[Theorem_0001[LHS]].begin() + ProofStackUInt64;
							const auto OPCODE = RHSRouteHistoryMap[Theorem_0001[LHS]].end();
							for (; opcode != OPCODE; ++opcode)
								Theorem_0001.emplace_back(*opcode);
							Theorem_0001[RHS] = Theorem_0001[LHS];

							// Is the FF queue still empty? //
							if (FastForwardTask_Thread.empty()) {
								bFastForwardFlag = true;
								FastForwardTask_Thread.push(Theorem_0001);
								break;
							}
						}
						Tasks_Thread.push(Theorem_0001);
					}

					if (theoremRHS % AxiomLHS == 0)
					{
						std::vector<BigInt128_t> Theorem_0002{ Theorem };
						Theorem_0002[RHS] = Theorem_0002[RHS] / AxiomLHS * AxiomRHS;
						Theorem_0002[last_UInt64] = Axiom[guid_UInt64];
						Theorem_0002.emplace_back(0x02); // Push opcode 0x02 onto the proofstack because we performed a _rhs _reduce operation) //
						Theorem_0002.emplace_back(Axiom[guid_UInt64]); // Push the Axiom ID onto the proofstack //
						__stdlog__({ "rhs_reduce in Module_0002 via Axiom_", Axiom[guid_UInt64].str(), " {" , Theorem_0002[LHS].str(), ", ", Theorem_0002[RHS].str(), "}" });

						// Commit for later fast-forward //
						if (RHSRouteHistoryMap.find(Theorem_0002[RHS]) == RHSRouteHistoryMap.end())
							RHSRouteHistoryMap.emplace(Theorem_0002[RHS], Theorem_0002);

						// Attempt fast-forward //
						if (LHSRouteHistoryMap.find(Theorem_0002[RHS]) != LHSRouteHistoryMap.end()) {
							//std::cout << "Proof found in Module_0002 via Fast-Forward (FF)" << " {" << Theorem_0002[RHS].str() << ", " << Theorem_0002[RHS].str() << "}" << std::endl;
							__stdlog__({ "Proof found in Module_0002 via Fast-Forward (FF)" });
							auto opcode = LHSRouteHistoryMap[Theorem_0002[RHS]].begin() + ProofStackUInt64;
							const auto OPCODE = LHSRouteHistoryMap[Theorem_0002[RHS]].end();
							for (; opcode != OPCODE; ++opcode)
								Theorem_0002.emplace_back(*opcode);
							Theorem_0002[LHS] = Theorem_0002[RHS];

							// Is the FF queue still empty? //
							if (FastForwardTask_Thread.empty()) {
								bFastForwardFlag = true;
								FastForwardTask_Thread.push(Theorem_0002);
								break;
							}
						}
						Tasks_Thread.push(Theorem_0002);
					}

					if (theoremRHS % AxiomRHS == 0)
					{
						std::vector<BigInt128_t> Theorem_0003{ Theorem };
						Theorem_0003[RHS] = Theorem_0003[RHS] / AxiomRHS * AxiomLHS;
						Theorem_0003[last_UInt64] = Axiom[guid_UInt64];
						Theorem_0003.emplace_back(0x03); // Push opcode 0x03 onto the proofstack because we performed a _rhs _expand operation) //
						Theorem_0003.emplace_back(Axiom[guid_UInt64]); // Push the Axiom ID onto the proofstack //
						__stdlog__({ "rhs_expand in Module_0003 via Axiom_", Axiom[guid_UInt64].str(), " {", Theorem_0003[LHS].str(), ", ", Theorem_0003[RHS].str(), " }" });

						// Commit for later fast-forward //
						if (RHSRouteHistoryMap.find(Theorem_0003[RHS]) == RHSRouteHistoryMap.end())
							RHSRouteHistoryMap.emplace(Theorem_0003[RHS], Theorem_0003);

						// Attempt fast-forward //
						if (LHSRouteHistoryMap.find(Theorem_0003[RHS]) != LHSRouteHistoryMap.end()) {
							//std::cout << "Proof found in Module_0003 via Fast-Forward (FF)" << " {" << Theorem_0003[RHS].str() << ", " << Theorem_0003[RHS].str() << "}" << std::endl; //
							__stdlog__({ "Proof found in Module_0003 via Fast-Forward (FF)", " {", Theorem_0003[RHS].str(), ", ", Theorem_0003[RHS].str(), "}" });
							auto opcode = LHSRouteHistoryMap[Theorem_0003[RHS]].begin() + ProofStackUInt64;
							const auto OPCODE = LHSRouteHistoryMap[Theorem_0003[RHS]].end();
							for (; opcode != OPCODE; ++opcode)
								Theorem_0003.emplace_back(*opcode);
							Theorem_0003[LHS] = Theorem_0003[RHS];

							// Is the FF queue still empty? //
							if (FastForwardTask_Thread.empty()) {
								bFastForwardFlag = true;
								FastForwardTask_Thread.push(Theorem_0003);
								break;
							}
						}
						Tasks_Thread.push(Theorem_0003);
					}

					__stdlog__({ "" });
				} // end for (...Axiom : InAxiomsStdStrVec) //
			} // end test (...Theorem[LHS] == Theorem[RHS]) //
		} // end for (...!Tasks_Thread.empty() && !QED)) //

		//*** End: Core Proof Engine (Loop) *** //

		__stdtraceout__("STDThreadProve\n");

		OutProofFound_FlagRef = QED;

		OutStatusReadyFlag = true; /* Set the Status Variable, last */

		return true;
	}

	enum class /*API_EXPORT*/ BracketType { CurlyBraces, SquareBrackets, Parentheses };

	template <BracketType type>
	struct BracketTraits {};

	template <>
	struct BracketTraits<BracketType::CurlyBraces>
	{
		static constexpr std::string Open = "{";
		static constexpr std::string Close = "}";
	};

	template <>
	struct BracketTraits<BracketType::SquareBrackets>
	{
		static constexpr std::string Open = "[";
		static constexpr std::string Close = "]";
	};

	template <>
	struct BracketTraits<BracketType::Parentheses>
	{
		static constexpr std::string Open = "(";
		static constexpr std::string Close = ")";
	};

	class /*API_EXPORT*/ CurlyBraceElide
	{
	public:
		/**
		Usage Example:
		std::vector<std::string> input = { "{", "{", "{", "1", "}", "}", "+", "{", "{", "1", "}", "}", "}", "=", "{", "{", "2", "}", "}" };
		const auto& output = CurlyBraceElide::Elide<BracketType::CurlyBraces>(input); // { "{", "1", "}", "+", "{", "1", "}", "=", "{", "2", "}" }
		*/
		template <BracketType type>
		static std::vector<std::string> Elide(const std::vector<std::string>& input)
		{
			static_assert( std::is_same_v<decltype( type ), BracketType>, "Invalid bracket type" );
			const std::string& openBrace = BracketTraits<type>::Open;
			const std::string& closeBrace = BracketTraits<type>::Close;
			std::vector<std::string> output;
			bool OpenScopeFlag = false;
			for (const std::string& c : input)
			{
				if (c == openBrace)
				{
					if (!OpenScopeFlag)
					{
						output.push_back(openBrace);
						OpenScopeFlag = true;
					}
					continue;
				} else if (c == closeBrace)
				{
					if (OpenScopeFlag)
					{
						output.push_back(closeBrace);
						OpenScopeFlag = false;
					}
					continue;
				}
				output.push_back(c);
			}
			return output;
		}
		/**
		Usage Example:
		const auto& output = CurlyBraceElide::Elide<BracketType::CurlyBraces>
		(
			{
				"{", "{", "{", "1", "}", "}", "+", "{", "{", "1", "}", "}", "}", "=", "{", "{", "2", "}", "}"
			}
		); // Output: { "{", "1", "}", "+", "{", "1", "}", "=", "{", "2", "}" }
		*/
		template <BracketType type>
		static std::vector<std::string> Elide(const std::initializer_list<std::string>& input)
		{
			static_assert( std::is_same_v<decltype( type ), BracketType>, "Invalid bracket type" );
			const std::vector<std::string>& input2(input);
			return Elide<type>(input2);
		}
	};

	template<BracketType EuclidBracket>
	class /*API_EXPORT*/ EuclidProver;

	template<>
	class /*API_EXPORT*/ EuclidProver<BracketType::CurlyBraces>
	{
	public:
		explicit EuclidProver
		(
			const std::string openBrace = "{",
			const std::string closeBrace = "}"
		) noexcept :
			_openBrace{ openBrace },
			_openBraceST{ "st" + openBrace },
			_closeBrace{ closeBrace }
		{

		}

		bool ProofFoundFlag{};
		bool StatusReadyFlag{};

		std::vector<
			std::vector<
			std::vector<
			std::string>>>
			ProofStep3DStdStrVec;

		std::vector<
			std::vector<
			std::string>>
			AxiomCommitLogStdStrVecRef;

		bool Axiom
		(
			const
			std::vector<
			std::string>&
			InAxiomConstStdStrVecRef
		)
		{
			return true;
		}

		bool Axiom
		(
			const
			std::initializer_list<
			std::string>&
			InAxiomInitListConstStdStringRef
		)
		{
			const std::vector<std::string>& InAxiomVecConstStdStringRef{ InAxiomInitListConstStdStringRef };
			return Axiom(InAxiomVecConstStdStringRef);
		}

		bool Axioms
		(
			const
			std::vector<
			std::vector<
			std::vector<
			std::string>>>&
			InAxiomsConstStdStrVec
		)
		{
			__stdtracein__("Axioms");

			AxiomsStdStrVec = InAxiomsConstStdStrVec;

			__stdtraceout__("Axioms");
			return true;
		}

		bool Axioms
		(
			const
			std::initializer_list<
			std::vector<
			std::vector<
			std::string>>>& InAxiomInitListConstStdStringRef
		)
		{
			const
				std::vector<
				std::vector<
				std::vector<
				std::string>>>&
				TempInAxiomsConstStdStrVecRef{ InAxiomInitListConstStdStringRef };

			return Axioms(TempInAxiomsConstStdStrVecRef);
		}

		bool Lemma
		(
			const
			std::vector<
			std::string>&
			InLemmaConstStdStringVecRef
		)
		{
			return true;
		}

		bool Lemma
		(
			const
			std::initializer_list<
			std::string>&
			InLemmaConstStdStrInitListRef
		)
		{
			const std::vector<std::string>& InLemmaConstStdStrVecRef{ InLemmaConstStdStrInitListRef };
			return Lemma(InLemmaConstStdStrVecRef);
		}

		bool Lemmas
		(
			const
			std::vector<
			std::vector<
			std::vector<
			std::string>>>&
			InLemmasConstStdStrVec
		)
		{
			return true;
		}

		bool Lemmas
		(
			const
			std::initializer_list<
			std::vector<
			std::vector<
			std::string>>>&
			InLemmasInitListConstStdStrVec
		)
		{
			const
				std::vector<
				std::vector<
				std::vector<
				std::string>>>&
				TempInLemmasConstStdStrVecRef{ InLemmasInitListConstStdStrVec };

			return Lemmas(TempInLemmasConstStdStrVecRef);
		}

		void Prove
		(
			const
			std::vector<
			std::vector<
			std::string>>&
			InProofStdStrVecRef
		)
		{
			__stdtracein__("Prove");

			Reset();

			//ProofStep3DStdStrVec = OutPath3DStdStrVecRef; //
			//TheoremStdStrVec = InProofStdStrVecRef; //
			//AxiomCommitLogStdStrVecRef = OutAxiomCommitLogStdStrVecRef; //
			/*
			{
				{"1", "+", "1", "+", "1", "+", "1"}, // (lhs) Prime Composite: 1585615607 //
				{"4"} // (rhs) Prime Composite: 29 //
			};
			*/
			/*th = */std::async
			(
				std::launch::async,
				__Prove__,
				std::cref(InProofStdStrVecRef),
				std::cref(AxiomsStdStrVec),
				std::ref(ProofFoundFlag),
				std::ref(StatusReadyFlag),
				std::ref(ProofStep3DStdStrVec),
				std::ref(AxiomCommitLogStdStrVecRef)
			);
			//th.get();//
			//print_path(ProofStep3DStdStrVec);//

			__stdtraceout__("Prove");

		}

		void Prove
		(
			const
			std::initializer_list<
			std::vector<
			std::string>>&
			InProofInitListConstStdStrVecRef
		)
		{
			const
				std::vector<
				std::vector<
				std::string>>&
				InProofVecConstCharRef{ InProofInitListConstStdStrVecRef };

			Prove(InProofVecConstCharRef);
		}

		bool StatusReady()
		{
			__stdtracein__("StatusReady");

			if (th.valid())
				th.get();

			__stdtraceout__("StatusReady");
			return StatusReadyFlag;
		}

		// Handle case when T is not a vector //
		template <typename T>
		typename std::enable_if<!std::is_same<T, std::vector<typename T::value_type>>::value, void>::type
			PrintPath(const T& element) {
			std::cout << " " << element << " ";
		};

		// Handle case when T is a vector //
		template <typename T>
		typename std::enable_if<std::is_same<T, std::vector<typename T::value_type>>::value, void>::type
			PrintPath(const T& vector) {
			// Add a newline and indent each level of depth //
			std::cout << std::string(depth % 2, '\n') << "{ ";
			depth++;
			for (const auto& element : vector) {
				PrintPath(element);
			}
			depth--;
			std::cout << " }";
		};

	private:
		std::size_t depth = 0;

		const std::string _openBrace;
		const std::string _openBraceST;
		const std::string _closeBrace;

		//std::thread th; //
		std::future<int> th;

		std::vector<
			std::vector<
			std::vector<
			std::string>>>
			AxiomsStdStrVec{};

		std::vector<
			std::vector<
			std::string>>
			TheoremStdStrVec{};

		void Reset()
		{
			__stdtracein__("Reset");

			StatusReadyFlag = false;
			ProofFoundFlag = false;

			__stdtraceout__("Reset");
		};
	};

	template<>
	class /*API_EXPORT*/ EuclidProver<BracketType::Parentheses> : public EuclidProver<BracketType::CurlyBraces>
	{
	public:
		EuclidProver() noexcept : EuclidProver<BracketType::CurlyBraces>("(", ")")
		{

		}
	};

	template<>
	class /*API_EXPORT*/ EuclidProver<BracketType::SquareBrackets> : public EuclidProver<BracketType::CurlyBraces>
	{
	public:
		EuclidProver() noexcept : EuclidProver<BracketType::CurlyBraces>("[", "]")
		{

		}
	};
}

using EuclidProverClass =

Euclid_Prover::EuclidProver<
	Euclid_Prover::BracketType::CurlyBraces>;
```

This is a specific example. Another real-world language model may require a different or perhaps more complex arbitrator function for semantic representation objects. Furthermore, considering the vast amount of data that these models need to process, careful attention should be paid to the efficiency of the arbitrator function, as it could significantly impact the performance of the model.

It's worth mentioning that using such a mapping system wouldn't replace the need for training a language model on a large corpus of text. Rather, it could be a way of encoding certain pre-defined mappings that the model should adhere to.

These containers would be particularly useful in the realm of theorem proving, network emulation, large language model development, ontology mapping, and any situation where one needs to handle many-to-one or many-to-many relationships based on semantic equivalence. They can vastly simplify the process of mapping varied representations of a concept to a single semantic entity, and managing the complexity of dealing with ambiguous keys.

## Conclusion
The proposed `std::reduction_map` and `std::reduction_multimap` extend the capabilities of `std::map` and `std::multimap` by introducing the concept of semantic equivalence of keys, and can provide an efficient and elegant way to handle complex key-value relationships in a variety of use cases.

Regards, 
Abdul S.
