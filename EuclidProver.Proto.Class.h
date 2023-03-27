/*
Provide a C++20 class called, Auto, that accepts two inputs in its constructor: Proof, of type `Axiom`; and Axioms, of type `std::vector<Axiom>`. 

Auto has an attribute, bProofFoundFlag, of type `bool`.

Auto has another attribute, Theorem, which itself has two attributes: LHS and RHS, which are of the same subclass type. LHS and RHS both has an attribute, PrimaryKey, of type `uint64_t`. LHS and RHS both has an attribute, Subnet, of type `std::vector<std::string>`. Auto also has an attribute, ProofHistoryMap, of type `std::unordered_map<uint64_t>`.

The `Axiom` class or struct also has an attribute, PrimaryKeyLHS, of type `uint64_t`, and an attribute, PrimaryKeyRHS, of type `uint64_t`. `Axiom` has another attribute, Subnet, of type `std::vector<std::string>`. `Axiom` also has another attribute, Indir, of enum class type, `Indirection`. Indirection has three available members: `reduce, expand, auto`. Indir's default value is set to `Indirection::auto`. Axiom also has an attribute, guid, of type `uint64_t`. 

After the Auto class accepts its Proof and Axioms parameters, Auto then spawns two threads, from an available thread pool of 128 threads, and, along with all necessary parameters (ProofHistoryMap, Indir, Axioms, ProofStack, Axiom), assigns a thread to each lambda: Expand, and Reduce, and the threads are invoked.

Reduce has a return type of `void`, and accepts the parameters supplied by class, Auto. Reduce only continues if `bProofFoundFlag == false` and Axiom.guid is not in ProofHistoryMap. In Reduce, a lambda called, SubnetFound, of return type `bool`, accepts four parameters: ProofHistoryMap, of type, `std::unordered_map<uint64_t>`;PrimaryKey, of type `uint64_t`; Axiom of type `Axiom`; and Indir of enum class type, `Indirection`. If Axiom.guid is not in ProofHistoryMap, it is inserted, and the lambda, SubnetFound, returns the following boolean comparison: `((PrimaryKey % Axiom.PrimaryKeyLHS) == 0)`. If SubnetFound returns `true`, up to four operations may then be performed inside Reduce: Axiom is pushed onto ProofStack; PrimaryKey is updated: `PrimaryKey = (PrimaryKey / Axiom.PrimaryKeyLHS * Axiom.PrimaryKeyRHS)`; another thread from the thread pool is assigned the lambda, Reduce, and the necessary parameters are supplied, and the thread is invoked; and, if Indir == `Indirection::auto`, then another thread is also assigned to Expand, the necessary parameters are supplied to it, and the thread is also invoked. 

Expand has a return type of `void`, and accepts the parameters supplied by class, Auto. Expand only continues if `bProofFoundFlag == false` and Axiom.guid is not in ProofHistoryMap. In Expand, a lambda called, SubnetFound, of return type `bool`, accepts four parameters: ProofHistoryMap, of type, `std::unordered_map<uint64_t>`; PrimaryKey, of type `uint64_t`; Axiom of type `Axiom`; and Indir of enum class type, `Indirection`. If Axiom.guid is not in ProofHistoryMap, it is inserted and the lambda, SubnetFound, returns the following boolean comparison: `((PrimaryKey % Axiom.PrimaryKeyRHS) == 0)`. If SubnetFound returns `true`, up to four operations may then be performed inside Expand: Axiom is pushed onto ProofStack; Axiom.guid is added to ProofHistoryMap; PrimaryKey is updated: `PrimaryKey = (PrimaryKey / Axiom.PrimaryKeyRHS * Axiom.PrimaryKeyLHS)`; another thread from the thread pool is assigned the lambda, Expand, and the necessary parameters are supplied, and the thread is invoked; and, if Indir == `Indirection::auto`, then another thread is also assigned to Reduce, the necessary parameters are supplied to it, and the thread is also invoked. 
*/

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <stack>

enum class Indirection
{
	reduce_,
	expand_,
	auto_
};

class Axiom
{
public:
	uint64_t PrimaryKeyLHS;
	uint64_t PrimaryKeyRHS;
	std::vector<std::string> Subnet;
	uint64_t guid;
};

class Auto
{
public:
	Auto(const Axiom& Proof, const std::vector<Axiom>& Axioms) :
		LHS.PrimaryKey(Proof.PrimaryKeyLHS), 
		RHS.PrimaryKey(Proof.PrimaryKeyRHS)
	{
		ThreadPool.reserve(ThreadPoolSize);
		// Spawn the initial threads for Expand and Reduce
		{
			std::unique_lock<std::mutex> lock(Mutex);
			CV.wait(lock, [this]() { return AvailableThreads >= 2; });
			AvailableThreads -= 2;
		}

		ThreadPool.emplace_back([&]()
		{
			Expand(LHS, Proof, ProofHistoryMap, Proof.Indir);
			{
				std::unique_lock<std::mutex> lock(Mutex);
				++AvailableThreads;
				CV.notify_one();
			}
		});

		ThreadPool.emplace_back([&]()
		{
			Reduce(RHS, Proof, ProofHistoryMap, Proof.Indir);
			{
				std::unique_lock<std::mutex> lock(Mutex);
				++AvailableThreads;
				CV.notify_one();
			}
		});

		// Wait for threads to complete
		for (auto& thread : ThreadPool)
		{
			thread.join();
		}
	}

private:
	class Theorem
	{
	public:
		uint64_t PrimaryKey;
		std::vector<std::string> Subnet;
	};

	Theorem LHS, RHS;
	bool bProofFoundFlag = false;
	std::unordered_map<uint64_t> ProofHistoryMap;
	std::stack<Axiom> ProofStack;
	enum class Indirection indir = Indirection::auto_;

	void Expand(Theorem& theorem, Axiom axiom, std::unordered_map<uint64_t>& proofHistoryMap, Axiom::Indirection indir)
	{
	// ... (implementation of Expand)
	};
	void Reduce(Theorem& theorem, Axiom axiom, std::unordered_map<uint64_t>& proofHistoryMap, Axiom::Indirection indir)
	{
	// ... (implementation of Reduce)
	};

	static constexpr size_t ThreadPoolSize = 128;
	std::vector<std::thread> ThreadPool;
	std::mutex Mutex;
	std::condition_variable CV;
	size_t AvailableThreads = ThreadPoolSize;
};