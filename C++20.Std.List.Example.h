/*
Sure, here is a C++20 implementation example for std::list<>:
C++
*/
#include <list>

template <typename T>
class list {
 public:
  // Constructors
  list() = default;
  list(std::initializer_list<T> list) : elements(list) {}

  // Destructor
  ~list() {
    for (auto it = elements.begin(); it != elements.end(); ++it) {
      delete *it;
    }
  }

  // Capacity
  size_t size() const { return elements.size(); }
  bool empty() const { return elements.empty(); }

  // Element access
  T& front() { return *elements.begin(); }
  const T& front() const { return *elements.begin(); }
  T& back() { return *elements.rbegin(); }
  const T& back() const { return *elements.rbegin(); }

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
  using iterator = typename std::list<T>::iterator;
  using const_iterator = typename std::list<T>::const_iterator;
  iterator begin() { return elements.begin(); }
  const_iterator begin() const { return elements.begin(); }
  iterator end() { return elements.end(); }
  const_iterator end() const { return elements.end(); }

 private:
  std::list<T> elements;
};
/*
Use code with caution. Learn more

This implementation of std::list<> supports the following operations:

    Constructors:
        Default constructor
        Initializer list constructor
    Destructor
    Capacity:
        size()
        empty()
    Element access:
        front()
        back()
    Modifiers:
        push_front()
        push_back()
        pop_front()
        pop_back()
    Iterators:
        begin()
        end()

This implementation is not complete, as it does not support all of the operations defined by the C++ standard for std::list<>. However, it provides a good starting point for implementing this container in C++20.
Sources
1. 
github.com/mootshell/EasyAsPly
subject to license (MIT)
2. 
github.com/faithandbrave/Shand 
*/
