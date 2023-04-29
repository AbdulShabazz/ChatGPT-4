#include <vector>

struct MyClass {
  int x;
  int y;

  MyClass(int x, int y) : x(x), y(y) {}
};

int main() {
  std::vector<MyClass> v;

  // This will create a temporary MyClass object, copy it into the vector, and then destroy the temporary object.
  v.push_back(MyClass(1, 2));

  // This will construct a MyClass object in-place in the vector, without creating a temporary object.
  v.emplace_back(1, 2);

  // Note that the performance of `push_back` and `emplace_back` will depend on the type of object being added to the vector. For built-in types, there is no difference in performance. For class types, `emplace_back` is typically more efficient than `push_back`.

  return 0;
}
