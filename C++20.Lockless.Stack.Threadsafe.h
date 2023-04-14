
#include <atomic>
#include <memory>
#include <optional>

template<typename T>
class LockFreeStack {
public:
	class ScopedPush {
	public:
		ScopedPush(LockFreeStack& stack, const T& value) : stack_(stack) {
			stack_.push(value);
		}

		~ScopedPush() {
			stack_.pop();
		}

	private:
		LockFreeStack& stack_;
	};

	void push(const T& value) {
		NodePtr new_node = std::make_shared<Node>(value);
		new_node->next = head.load(std::memory_order_relaxed);
		while (!head.compare_exchange_weak(new_node->next, new_node,
										   std::memory_order_release,
										   std::memory_order_relaxed))
			; // Retry until successful
	}

	std::optional<T> pop() {
		NodePtr old_head = head.load(std::memory_order_relaxed);
		while (old_head && !head.compare_exchange_weak(old_head, old_head->next,
													   std::memory_order_acquire,
													   std::memory_order_relaxed))
			; // Retry until successful

		return old_head ? std::make_optional(old_head->value) : std::nullopt;
	}

private:
	struct Node {
		T value;
		std::shared_ptr<Node> next;

		explicit Node(const T& value) : value(value), next(nullptr) {}
	};

	using NodePtr = std::shared_ptr<Node>;

	std::atomic<NodePtr> head;
};

// Usage example of a copy-on-write lockless threadsafe stack
#include <iostream>

int main() {
	LockFreeStack<int> stack;

	{
		LockFreeStack<int>::ScopedPush scoped_push(stack, 42);
		std::cout << "Value pushed onto the stack: 42" << std::endl;
	} // The value 42 will be popped from the stack when the ScopedPush object goes out of scope

	auto value = stack.pop();
	if (value) {
		std::cout << "Unexpected value popped from the stack: " << *value << std::endl;
	} else {
		std::cout << "Stack is empty, as expected" << std::endl;
	}

	return 0;
}

