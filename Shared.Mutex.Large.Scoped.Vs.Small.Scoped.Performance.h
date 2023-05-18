`/*Q:Which c++20 version is more performant?*/
// version 1
{
	std::unique_lock<std::shared_mutex> lock(rhsMutex);
	// Attempt fast-forward //
	if (RHSRouteHistoryMap.find(Theorem_0000[LHS]) != RHSRouteHistoryMap.end()) {
		//std::cout << "Proof found in Module_0000 via Fast-Forward (FF)" << " {" << Theorem_0000[LHS].str() << ", " << Theorem_0000[LHS].str() << "}" << std::endl;
		__stdlog__({ "Proof found in Module_0000 via Fast-Forward (FF)" });
		auto opcode = RHSRouteHistoryMap[Theorem_0000[LHS]].begin() + ProofStackUInt64;
		const auto OPCODE = RHSRouteHistoryMap[Theorem_0000[LHS]].end();
		for (opcode; opcode != OPCODE; ++opcode)
			Theorem_0000.emplace_back(*opcode);
		Theorem_0000[RHS] = Theorem_0000[LHS];
	}
}

// version 2
	// Attempt fast-forward //
	if (RHSRouteHistoryMap.find(Theorem_0000[LHS]) != RHSRouteHistoryMap.end()) {
		//std::cout << "Proof found in Module_0000 via Fast-Forward (FF)" << " {" << Theorem_0000[LHS].str() << ", " << Theorem_0000[LHS].str() << "}" << std::endl;
		__stdlog__({ "Proof found in Module_0000 via Fast-Forward (FF)" });
		auto opcode {};
		const auto OPCODE {};
		{
			std::unique_lock<std::shared_mutex> lock(rhsMutex);
				opcode = RHSRouteHistoryMap[Theorem_0000[LHS]].begin() + ProofStackUInt64;
		}
		{
			std::unique_lock<std::shared_mutex> lock(rhsMutex);
				OPCODE = RHSRouteHistoryMap[Theorem_0000[LHS]].end();
		}
		for (opcode; opcode != OPCODE; ++opcode)
			Theorem_0000.emplace_back(*opcode);
		Theorem_0000[RHS] = Theorem_0000[LHS];
	}
`
/*
In the provided code snippets, the main difference between Version 1 and Version 2 
lies in where and how the mutex locking is done. Mutexes are used to prevent data races 
in multithreaded programs by ensuring that only one thread can access a specific piece of data at a time. 

Version 1 locks the mutex at the beginning of the block and unlocks it at the end. 
The lock is held during the entire duration of the execution of the code block. 
This means that any other thread trying to acquire this lock will be blocked until the lock is released. 

On the other hand, Version 2 locks the mutex twice, but for shorter periods of time. 
It locks the mutex, accesses the shared data, then releases the lock. It then repeats 
this process again. This approach reduces the duration the lock is held, potentially allowing 
other threads to access the shared data between the lock and unlock operations.

In terms of performance, it largely depends on the specifics of your program and the environment 
it's running in. However, here are a few general principles:

- If the `RHSRouteHistoryMap` is a large data structure or the time between `begin` and `end` calls 
is significant, Version 2 could be faster, as it reduces the time the lock is held, 
potentially improving concurrency by allowing other threads to interact with the map between the two locks.

- However, acquiring and releasing a lock has its own overhead. So, if the operation protected by the lock 
is quick, the cost of locking and unlocking twice (as in Version 2) might outweigh the benefits of holding the lock for a shorter time.

- Additionally, in Version 2, there is a possibility of the data being modified between the two lock-unlock cycles, 
which might lead to incorrect behavior if your logic assumes that the data remains consistent throughout the operation.

To summarize, in a multi-threaded environment, Version 2 could potentially provide better performance if 
it increases the overall concurrency and if the cost of the extra lock/unlock operation is less than the benefits 
gained from increased concurrency. However, it introduces a potential data race which might lead to incorrect behavior. 
If the consistency of the data between the two operations is crucial, then Version 1, despite potentially lower performance, 
would be the safer choice.
*/
