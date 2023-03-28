/*
Q:How can you emulate the javascript event listener framework in c++20?

A:While C++ and JavaScript are fundamentally different languages, you can still create a basic event listener framework in C++20 that emulates the one in JavaScript. Here's a simple example of how you might achieve this:

	Define an EventListener class:

cpp
*/
#include <functional>
#include <map>
#include <string>
#include <vector>

class EventListener {
public:
	using Callback = std::function<void()>;

	void on(const std::string &event, const Callback &callback) {
		_listeners[event].push_back(callback);
	}

	void emit(const std::string &event) {
		auto it = _listeners.find(event);
		if (it != _listeners.end()) {
			for (const auto &callback : it->second) {
				callback();
			}
		}
	}

private:
	std::map<std::string, std::vector<Callback>> _listeners;
};
/*
A:Now, you can use this EventListener class to create your event listeners and emit events:

cpp
*/
#include <iostream>

int main() {
	EventListener eventListener;

	eventListener.on("hello", []() {
		std::cout << "Hello, World!" << std::endl;
	});

	eventListener.on("hello", []() {
		std::cout << "Another listener for the same event!" << std::endl;
	});

	eventListener.on("goodbye", []() {
		std::cout << "Goodbye, World!" << std::endl;
	});

	eventListener.emit("hello");
	eventListener.emit("goodbye");
	eventListener.emit("nonexistent");

	return 0;
}
/*
Now, when you run this example, you will see the following output:

csharp

Hello, World!
Another listener for the same event!
Goodbye, World!

This simple event listener framework allows you to register callbacks for specific events using the on method and trigger those callbacks by emitting the events with the emit method. Note that this example doesn't include removing event listeners or event propagation, but you can extend the EventListener class to incorporate these features if needed.
*/