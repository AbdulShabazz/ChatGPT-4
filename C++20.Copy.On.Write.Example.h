#include <iostream>
#include <memory>
#include <string>

class CowString {
public:
	CowString() : data(std::make_shared<std::string>()) {}
	
	explicit CowString(const std::string& str) : data(std::make_shared<std::string>(str)) {}

	CowString(const CowString& other) : data(other.data) {}

	CowString& operator=(const CowString& other) {
		if (this != &other) {
			data = other.data;
		}
		return *this;
	}

	char operator[](size_t pos) const {
		return (*data)[pos];
	}

	char& operator[](size_t pos) {
		detach(); // (Deep) Copy-on-write
		return (*data)[pos];
	}

	size_t size() const {
		return data->size();
	}

private:
	void detach() {
		if (!data.unique()) {
			data = std::make_shared<std::string>(*data);
		}
	}

	std::shared_ptr<std::string> data;
};

int main() {
	CowString str1("Hello, World!");
	CowString str2 = str1;

	std::cout << "Before modification: " << std::endl;
	std::cout << "str1: " << *str1.data << std::endl;
	std::cout << "str2: " << *str2.data << std::endl;

	str2[0] = 'M';

	std::cout << "After modification: " << std::endl;
	std::cout << "str1: " << *str1.data << std::endl;
	std::cout << "str2: " << *str2.data << std::endl;

	return 0;
}

/*
In this example, CowString is a custom container class that stores a shared pointer to an std::string. The copy constructor and assignment operator create shallow copies of the shared pointer, ensuring that the resource is shared between instances. When modifying an instance of CowString, the detach method is called, which checks if the shared pointer has a unique owner. If not, it creates a deep copy of the underlying resource, ensuring that modifications are only made to the new copy, effectively implementing a copy-on-write mechanism.

When you run the example, you'll see that the two instances of CowString share the same resource initially. After modifying str2, they will have their own separate resources.

Note that this example is not meant to be an efficient or complete implementation of a string class. It's intended to demonstrate the basic principles of a copy-on-write architecture in C++20. In real-world scenarios, you might need to optimize memory allocation and deallocation, and provide additional functionality depending on your requirements.
*/
