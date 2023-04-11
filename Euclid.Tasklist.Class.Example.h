
//#include "../boost/multiprecision/cpp_int.hpp"
//#include "../EuclidProverLibDLL/EuclidProverLibDLL.h"
//#include "../EuclidProverLibDLL/TestCases.h"

#include <vector>
#include <chrono>
#include <iostream>
#include <thread>
#include <unordered_map>

#include <algorithm>
#include <cstdint>
/*
Q:Is there a Listener/Broadcast configuration or architecture which could be a solution?

Yes, a Listener/Broadcast (or Publisher/Subscriber) architecture can be a solution to avoid contention in accessing the unordered_map. In this pattern, Axioms (listeners/subscribers) register themselves to receive updates from a central source (broadcast/publisher) when a change occurs, instead of directly accessing the shared data structure. This reduces contention and avoids the need for fine-grained locking.

Here's a high-level example of how you can implement a Listener/Broadcast architecture:

    Define an AttributeListener interface and a TaskListClass class:

cpp
 */
class AttributeListener {
public:
    virtual void onAttributeChanged(uint64_t key, uint64_t new_value) = 0;
};

/*
    Make your Axioms inherit from AttributeListener:

cpp
 */
class AxiomClass : public AttributeListener {
public:
    AxiomClass(const uint64_t key) : 
        key(key) 
    {
    }

    void onAttributeChanged(const uint64_t key, uint64_t new_value) override final {
        if (this->key == key) {
            attribute = new_value;
        }
    }

    uint64_t GetGUID_UInt64() const {
        return guid;
    }

    std::vector<AxiomClass> GetProofStack__AxiomClassVec() {
        return ProofStack_AxiomClassVec;
    }

    // Copy constructor
    explicit AxiomClass(const AxiomClass& other) :
        guid(other.guid),
        key(other.key),
        attribute(other.attribute),
        ProofStack_AxiomClassVec(other.ProofStack_AxiomClassVec)
    {
    }

    // Move constructor
    explicit AxiomClass(AxiomClass&& other) noexcept :
        guid(std::move(other.guid)),
        key(std::move(other.key)),
        attribute(std::move(other.attribute)),
        ProofStack_AxiomClassVec(std::move(other.ProofStack_AxiomClassVec))
    {
    }

    // Copy assignment operator
    AxiomClass& operator=(const AxiomClass& other)
    {
        if (this != &other)
        {
            *this = AxiomClass(other);
        }
        return *this;
    }

    // Move assignment operator
    AxiomClass& operator=(const AxiomClass&& other) noexcept
    {
        if (this != &other)
        {
            *this = AxiomClass(std::move(other));
        }
        return *this;
    }

    // Destructor
    ~AxiomClass() = default;

private:
    // Todo: These should be atomics
    const uint64_t guid;
    const uint64_t key;
    uint64_t attribute = 1;
    std::vector<AxiomClass> ProofStack_AxiomClassVec{};
};

// Todo: Only archive PrimaryKey_UInt64 and ProofStack_AxiomClassVec
// Todo: refactor down to only these members: 1. addListener, 2. GetGUID_UInt64, 3. GetProofStack_AxiomClassVec

class TaskListClass {
public:
    void addListener(const uint64_t InIdxUInt64, AxiomClass& listener) {
        std::vector<AxiomClass&> obj{};
        obj.push_back(listener);
        listeners.emplace(InIdxUInt64,obj);
    }

    void notifyAttributeChanged(const uint64_t key, const uint64_t new_value, const uint64_t guid) {
        auto it = listeners.find(key);
        if (it != listeners.end() && it->second.GetGUID_UInt64() != guid) {
            it->second.onAttributeChanged(key, new_value);
        }
        else if (it->second.GetGUID_UInt64() != guid) {
            AxiomClass obj(new_value);
            addListener(key, obj);
        }
    }

private:
    std::unordered_map<const uint64_t, AxiomClass&> listeners;
    uint64_t IdxUInt64 = 0;
};
/*
    TaskListClass, in tandem with std::for_each(std::execute::par,*.begin(), *.end()) or std::thread, emulates unordered_map parallel read/write access.
    Use the TaskListClass to propagate attribute changes:

cpp
 */
int main() {
    TaskListClass TaskListLHS;

    // Create Axioms and register them as listeners
    std::vector<AxiomClass> Axioms;
    for (uint64_t i = 0; i < 1000; ++i) {
        Axioms.emplace_back(i);
        TaskListLHS.addListener(i, Axioms.back());
    }

    // Update an attribute and broadcast the change
    const uint64_t guid = 10;
    const uint64_t key = 42;
    const uint64_t new_value = 12345;
    TaskListLHS.notifyAttributeChanged(key, new_value, guid);

    return 0;
}
/*
In this example, the Axioms no longer need to access the shared unordered_map to read each other's attribute values. Instead, they receive updates through the onAttributeChanged method when an attribute changes. This reduces contention and simplifies synchronization.

However, this approach has some trade-offs:

    It increases memory usage since each object stores its attribute value.
    It can increase communication overhead, as each update must be broadcast to all listeners.
    It may not be suitable for scenarios where you need to query an object's attribute value at any given time, as the broadcast is only sent when an attribute is updated.

You should consider these trade-offs when deciding if the Listener/Broadcast architecture is the right solution for your use case.
 */


//int main()
//{
//    /*
//	//using namespace EuclidProverLib;
//
//	// Instantiate Prover (module)
//	
//    EuclidProver<BracketType::CurlyBraces> Euclid{};
//
//	const std::vector<std::string>& axiom_0 = { "{", "1", "}","+","{", "1", "}","=","{", "2", "}" };
//	Euclid.Axiom( axiom_0 );
//
//    
//	//x86i64IntTestCases{};    
//
//    std::vector<int> input{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//    std::vector<int> output(input.size());
//    std::vector<std::jthread> workers;
//
//    workers.reserve(1); // thread pool size
//
//    const auto start_time_op = std::chrono::high_resolution_clock::now();
//    workers.emplace_back([&input, &output]() { output[0] = input[0] * input[0]; }); // 1115400 ns (vs 11176100 ns w/o workers.reserve(...)
//    const auto end_time_op = std::chrono::high_resolution_clock::now();
//    const auto duration_op = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_op - start_time_op).count();
//    std::cout << "thread(...) duration: " << duration_op << "_ns" << std::endl;
//    */
//
//    return 0;
//
//}

//#include "../boost/multiprecision/cpp_int.hpp"
//#include "../EuclidProverLibDLL/EuclidProverLibDLL.h"
//#include "../EuclidProverLibDLL/TestCases.h"

#include <vector>
#include <chrono>
#include <iostream>
#include <thread>
#include <unordered_map>

#include <algorithm>
#include <cstdint>
/*
Q:Is there a Listener/Broadcast configuration or architecture which could be a solution?

Yes, a Listener/Broadcast (or Publisher/Subscriber) architecture can be a solution to avoid contention in accessing the unordered_map. In this pattern, Axioms (listeners/subscribers) register themselves to receive updates from a central source (broadcast/publisher) when a change occurs, instead of directly accessing the shared data structure. This reduces contention and avoids the need for fine-grained locking.

Here's a high-level example of how you can implement a Listener/Broadcast architecture:

    Define an AttributeListener interface and a TaskListClass class:

cpp
 */
class AttributeListener {
public:
    virtual void onAttributeChanged(uint64_t key, uint64_t new_value) = 0;
};

/*
    Make your Axioms inherit from AttributeListener:

cpp
 */
class AxiomClass : public AttributeListener {
public:
    AxiomClass(const uint64_t key) : 
        key(key) 
    {
    }

    void onAttributeChanged(const uint64_t key, uint64_t new_value) override final {
        if (this->key == key) {
            attribute = new_value;
        }
    }

    uint64_t GetGUID_UInt64() const {
        return guid;
    }

    std::vector<AxiomClass> GetProofStack__AxiomClassVec() {
        return ProofStack_AxiomClassVec;
    }

    // Copy constructor
    explicit AxiomClass(const AxiomClass& other) :
        guid(other.guid),
        key(other.key),
        attribute(other.attribute),
        ProofStack_AxiomClassVec(other.ProofStack_AxiomClassVec)
    {
    }

    // Move constructor
    explicit AxiomClass(AxiomClass&& other) noexcept :
        guid(std::move(other.guid)),
        key(std::move(other.key)),
        attribute(std::move(other.attribute)),
        ProofStack_AxiomClassVec(std::move(other.ProofStack_AxiomClassVec))
    {
    }

    // Copy assignment operator
    AxiomClass& operator=(const AxiomClass& other)
    {
        if (this != &other)
        {
            *this = AxiomClass(other);
        }
        return *this;
    }

    // Move assignment operator
    AxiomClass& operator=(const AxiomClass&& other) noexcept
    {
        if (this != &other)
        {
            *this = AxiomClass(std::move(other));
        }
        return *this;
    }

    // Destructor
    ~AxiomClass() = default;

private:
    // Todo: These should be atomics
    const uint64_t guid;
    const uint64_t key;
    uint64_t attribute = 1;
    std::vector<AxiomClass> ProofStack_AxiomClassVec{};
};

// Todo: Only archive PrimaryKey_UInt64 and ProofStack_AxiomClassVec
// Todo: refactor down to only these members: 1. addListener, 2. GetGUID_UInt64, 3. GetProofStack_AxiomClassVec

class TaskListClass {
public:
    void addListener(const uint64_t InIdxUInt64, AxiomClass& listener) {
        std::vector<AxiomClass&> obj{};
        obj.push_back(listener);
        listeners.emplace(InIdxUInt64,obj);
    }

    void notifyAttributeChanged(const uint64_t key, const uint64_t new_value, const uint64_t guid) {
        auto it = listeners.find(key);
        if (it != listeners.end() && it->second.GetGUID_UInt64() != guid) {
            it->second.onAttributeChanged(key, new_value);
        }
        else if (it->second.GetGUID_UInt64() != guid) {
            AxiomClass obj(new_value);
            addListener(key, obj);
        }
    }

private:
    std::unordered_map<const uint64_t, AxiomClass&> listeners;
    uint64_t IdxUInt64 = 0;
};
/*
    TaskListClass, in tandem with std::for_each(std::execute::par,*.begin(), *.end()) or std::thread, emulates unordered_map parallel read/write access.
    Use the TaskListClass to propagate attribute changes:

cpp
 */
int main() {
    TaskListClass TaskListLHS;

    // Create Axioms and register them as listeners
    std::vector<AxiomClass> Axioms;
    for (uint64_t i = 0; i < 1000; ++i) {
        Axioms.emplace_back(i);
        TaskListLHS.addListener(i, Axioms.back());
    }

    // Update an attribute and broadcast the change
    const uint64_t guid = 10;
    const uint64_t key = 42;
    const uint64_t new_value = 12345;
    TaskListLHS.notifyAttributeChanged(key, new_value, guid);

    return 0;
}
/*
In this example, the Axioms no longer need to access the shared unordered_map to read each other's attribute values. Instead, they receive updates through the onAttributeChanged method when an attribute changes. This reduces contention and simplifies synchronization.

However, this approach has some trade-offs:

    It increases memory usage since each object stores its attribute value.
    It can increase communication overhead, as each update must be broadcast to all listeners.
    It may not be suitable for scenarios where you need to query an object's attribute value at any given time, as the broadcast is only sent when an attribute is updated.

You should consider these trade-offs when deciding if the Listener/Broadcast architecture is the right solution for your use case.
 */


//int main()
//{
//    /*
//	//using namespace EuclidProverLib;
//
//	// Instantiate Prover (module)
//	
//    EuclidProver<BracketType::CurlyBraces> Euclid{};
//
//	const std::vector<std::string>& axiom_0 = { "{", "1", "}","+","{", "1", "}","=","{", "2", "}" };
//	Euclid.Axiom( axiom_0 );
//
//    
//	//x86i64IntTestCases{};    
//
//    std::vector<int> input{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//    std::vector<int> output(input.size());
//    std::vector<std::jthread> workers;
//
//    workers.reserve(1); // thread pool size
//
//    const auto start_time_op = std::chrono::high_resolution_clock::now();
//    workers.emplace_back([&input, &output]() { output[0] = input[0] * input[0]; }); // 1115400 ns (vs 11176100 ns w/o workers.reserve(...)
//    const auto end_time_op = std::chrono::high_resolution_clock::now();
//    const auto duration_op = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_op - start_time_op).count();
//    std::cout << "thread(...) duration: " << duration_op << "_ns" << std::endl;
//    */
//
//    return 0;
//
//}
