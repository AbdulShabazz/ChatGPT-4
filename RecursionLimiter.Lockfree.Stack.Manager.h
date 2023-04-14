#include <atomic>
#include <stdexcept>

class RecursionLimiter {
public:
	static void set_recursion_limit(std::size_t limit) {
		recursion_limit = limit;
		recursive_calls_available = limit;
	}

	RecursionLimiter(std::size_t required_calls)
		: required_calls_(required_calls), acquired_(false) {
		while (!acquired_) {
			if (recursive_calls_available.fetch_sub(required_calls_, std::memory_order_acquire) >= required_calls_) {
				acquired_ = true;
			} else {
				recursive_calls_available.fetch_add(required_calls_, std::memory_order_release);
				std::this_thread::yield();
			}
		}
	}

	~RecursionLimiter() {
		if (acquired_) {
			recursive_calls_available.fetch_add(required_calls_, std::memory_order_release);
		}
	}

	bool acquired() const {
		return acquired_;
	}

private:
	static inline std::atomic<std::size_t> recursion_limit;
	static inline std::atomic<std::size_t> recursive_calls_available;
	std::size_t required_calls_;
	bool acquired_;
};

/ Set the recursion limit
RecursionLimiter::set_recursion_limit(1000);

// Usage
std::for_each(std::execution::par_unseq, Axioms_Vec.begin(), Axioms_Vec.end(),
    [&](const Axiom_Struct& Axiom) {
        RecursionLimiter limiter(3);
        if (limiter.acquired()) {
            Reduce(TheoremProto_0000, Axiom);
            Reduce(TheoremProto_0001, Axiom);
            Reduce(TheoremProto_0002, Axiom);
        }
    });
