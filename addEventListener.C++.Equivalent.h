/*Q:What is the C++20 equivalent for the following javascript?*/

addEventListner('ShowMessage', function(e) {
  console.log("ShowMessage: [",e.detail.message,"]");
},1);

postMessage('ShowMessage', {message: "Hello World"});
/* 
There isn't a direct equivalent for JavaScript's event handling and messaging in C++20, as C++ is not designed for web development like JavaScript. However, you can achieve a similar effect using the Observer pattern and standard C++20 features.

Here's an example of how you could achieve a similar result in C++20:

cpp
 */
#include <iostream>
#include <functional>
#include <vector>
#include <string>

class EventDispatcher {
public:
    void addEventListener(const std::function<void(const std::string&)>& callback) {
        listeners.push_back(callback);
    }

    void postMessage(const std::string& message) {
        for (const auto& listener : listeners) {
            listener(message);
        }
    }

private:
    std::vector<std::function<void(const std::string&)>> listeners;
};

int main() {
    EventDispatcher eventDispatcher;

    // Equivalent to addEventListener
    eventDispatcher.addEventListener([](const std::string& message) {
        std::cout << "ShowMessage: [" << message << "]" << std::endl;
    });

    // Equivalent to postMessage
    eventDispatcher.postMessage("Hello World");

    return 0;
}
/*
In this example, we create an EventDispatcher class that manages a list of listener functions. You can add listeners using the addEventListener method and trigger them with the postMessage method. This example uses lambda functions and the standard C++ library features.
*/
