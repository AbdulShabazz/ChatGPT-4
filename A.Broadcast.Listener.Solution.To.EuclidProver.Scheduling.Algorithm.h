/* 
Q:Is there a Listener/Broadcast configuration or architecture which could be a solution?

Yes, a Listener/Broadcast (or Publisher/Subscriber) architecture can be a solution to avoid contention in accessing the unordered_map. In this pattern, objects (listeners/subscribers) register themselves to receive updates from a central source (broadcast/publisher) when a change occurs, instead of directly accessing the shared data structure. This reduces contention and avoids the need for fine-grained locking.

Here's a high-level example of how you can implement a Listener/Broadcast architecture:

    Define an AttributeListener interface and a Broadcaster class:

cpp
 */
class AttributeListener {
public:
    virtual void onAttributeChanged(uint64_t key, uint64_t new_value) = 0;
};

class Broadcaster {
public:
    void addListener(const uint64_t IdxUInt64 = 0, AttributeListener& listener) {
        listeners[IdxUInt64] = &listener;
    }

    void notifyAttributeChanged(const uint64_t key, const uint64_t new_value) {
        auto it = listeners.find(key);
        if (it != listeners.end()) {
            it->second->onAttributeChanged(key, new_value);
        }
    }

private:
	std::unordered_map<const uint64_t,AttributeListener> listeners;
};
/* 
    Make your objects inherit from AttributeListener:

cpp
 */
class MyObject : public AttributeListener {
public:
    MyObject(const uint64_t key) : key(key) {}

    void onAttributeChanged(const uint64_t key, uint64_t new_value) override {
        if (this->key == key) {
            attribute = new_value;
        }
    }

private:
    const uint64_t key;
    uint64_t attribute = 1;
    // Other members...
};
/* 
    Use the Broadcaster to propagate attribute changes:

cpp
 */
int main() {
    Broadcaster broadcaster;

    // Create objects and register them as listeners
    std::vector<MyObject> objects;
    for (uint64_t i = 0; i < 1000; ++i) {
        objects.emplace_back(i);
        broadcaster.addListener(i, &objects.back());
    }

    // Update an attribute and broadcast the change
    uint64_t key = 42;
    uint64_t new_value = 12345;
    broadcaster.notifyAttributeChanged(key, new_value);

    return 0;
}
/* 
In this example, the objects no longer need to access the shared unordered_map to read each other's attribute values. Instead, they receive updates through the onAttributeChanged method when an attribute changes. This reduces contention and simplifies synchronization.

However, this approach has some trade-offs:

    It increases memory usage since each object stores its attribute value.
    It can increase communication overhead, as each update must be broadcast to all listeners.
    It may not be suitable for scenarios where you need to query an object's attribute value at any given time, as the broadcast is only sent when an attribute is updated.

You should consider these trade-offs when deciding if the Listener/Broadcast architecture is the right solution for your use case.
 */
