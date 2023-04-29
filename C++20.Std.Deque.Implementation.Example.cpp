#include <deque>

template <typename T>
class deque {
 public:
	// Constructors
	deque() = default;
	deque(std::initializer_list<T> list) : elements(list) {}

	// Destructor
	~deque() {
		for (auto it = elements.begin(); it != elements.end(); ++it) {
			delete *it;
		}
	}

	// Capacity
	size_t size() const { return elements.size(); }
	bool empty() const { return elements.empty(); }

	// Element access
	T& front() { return *elements.front(); }
	const T& front() const { return *elements.front(); }
	T& back() { return *elements.back(); }
	const T& back() const { return *elements.back(); }

	// Modifiers
	void push_front(const T& value) { elements.push_front(new T(value)); }
	void push_back(const T& value) { elements.push_back(new T(value)); }
	void pop_front() {
		delete elements.front();
		elements.pop_front();
	}
	void pop_back() {
		delete elements.back();
		elements.pop_back();
	}

	// Iterators
	using iterator = typename std::deque<T>::iterator;
	using const_iterator = typename std::deque<T>::const_iterator;
	iterator begin() { return elements.begin(); }
	const_iterator begin() const { return elements.begin(); }
	iterator end() { return elements.end(); }
	const_iterator end() const { return elements.end(); }

 private:
	std::deque<T> elements;
};
