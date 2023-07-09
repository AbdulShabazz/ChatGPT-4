# Proposal for including std::reduction_map and std::reduction_multimap in the C++26 Standard

## Abstract
We propose the addition of two new containers to the C++ Standard Template Library (STL): `std::reduction_map` and `std::reduction_multimap`. These containers are similar to `std::map` and `std::multimap`, but they include an additional component known as an `arbitrator function` that can transform different keys into a single, 'base' or 'canonical' form. This proposal aims to provide a general-purpose solution to map multiple keys to a single value or multiple values based on the principle of semantic equivalence.

## Description
### std::reduction_map
`std::reduction_map` is a type of associative container that stores elements formed by the combination of a key value and a mapped value. It is similar to `std::map`, but it uses an arbitrator function that can parse reduction_map keys for their semantic equivalence. In the absence of an arbitrator function, it defaults to the behavior of C++ `std::map`.

The signature for `std::reduction_map` could be:

```
template<
    typename Key, // map::key_type //
    typename T, // map::mapped_type //
    typename ArbitratorFunc = std::function<Key(const Key&)>, // arbitrator function //
    typename Compare = std::less<Key>, // map::key_compare //
    typename Alloc = std::allocator<std::pair<const Key, T>> // map::allocator_type //
> 
class reduction_map { /* ... */ };
```
The `ArbitratorFunc` is a new key-mapping function component that accepts a key as input and returns a 'base' or 'canonical' form of the key.

### std::reduction_multimap
`std::reduction_multimap` is similar to `std::reduction_map`, but its keys do not have to be unique, so it can have multiple pairs with equivalent keys. This makes it useful for representing many-to-many relationships. If no arbitrator function is provided, `std::reduction_multimap` defaults to the behavior of `std::multimap`!

The signature for `std::reduction_multimap` could be:

```
template<
    typename Key, // map::key_type //
    typename T, // map::mapped_type //
    typename ArbitratorFunc = std::function<Key(const Key&)>, // arbitrator function //
    typename Compare = std::less<Key>, // map::key_compare //
    typename Alloc = std::allocator<std::pair<const Key, T>> // map::allocator_type //
> 
class reduction_multimap { /* ... */ };
```

## Use Cases

For a real world use-case example, ontology mapping is a crucial aspect in many fields including Artificial Intelligence (AI), Natural Language Processing (NLP), and particularly in the development of large language models. Ontology mapping refers to the process of relating similar concepts from different ontologies, which is often necessary when integrating different data sources, developing interoperability between AI systems, or creating semantic web services.

In the context of large language model development, an important task is the semantic understanding and representation of words, phrases, or concepts. Often, there is a need to map different lexical or syntactical forms of a concept to the same semantic entity. This is where our proposed `std::reduction_map` and `std::reduction_multimap` can be particularly useful.

Let's consider an example use case:

Imagine we're developing a language model that has to understand and answer questions about mathematics. The model should be able to understand that the phrases "1", "one plus zero", "zero plus one", "1 + 0", and "0 + 1" all refer to the same concept, i.e., they all have the same result "1".

In this case, we could define our `std::reduction_map` with `std::string` as the key and an object representing the mathematical concept as the value. The ArbitratorFunc would be a function that can parse and simplify mathematical expressions. Therefore, all the different forms that represent the same concept would be mapped to the same object:

```
std::reduction_map<std::string, ArbitratorFunc, MathExpressionSimplifier> math_concepts;
math_concepts["1"] = "One";
math_concepts["1 + 0"]; // returns "One"; //
math_concepts["0 + 1"]; // returns "One"; //
math_concepts["one plus zero"]; // returns "One"; //
math_concepts["zero plus one"]; // returns "One"; //
```

After these insertions, the model would know that "1 + 0", "0 + 1", "one plus zero", and "zero plus one" all refer to the same concept, and it can treat them as semantically equivalent. It's clear how this can vastly simplify the process of mapping varied representations of a concept to a single semantic entity.

An example of an arbitrator function for this could be one such as the following:
```
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <functional>
#include <concepts>

template<typename T>
concept StringLike = requires(T a) {
	{ a } -> std::convertible_to<std::string>;
};

template<StringLike T = std::string>
std::function<std::string(const T&)> ArbitratorFunc = [](const T& key) -> std::string {
    std::stringstream ss(key);
	T item;
	int sum = 0;
    bool unsupported_string_flag = false;
	
	// Split string by ' ' //
	while (std::getline(ss, item, ' ')) {
		// Convert each item to its integer value to add to the sum //
		if (item == "1" || item == "0" ) {
			sum += std::stoi(item);
		} else if (item == "zero") {
			sum += 0;
		} else if (item == "one") {
			sum += 1;
		} else if (item == "plus" or item == "+") {
			continue;
		} else {
			unsupported_string_flag = true;
			break;
		}
	}
	
	if (!unsupported_string_flag) {
		return std::to_string(sum);
	} else {
		return key;
	}
};

```

This is a specific example. Another real-world language model may require a different or perhaps more complex arbitrator function for semantic representation objects. Furthermore, considering the vast amount of data that these models need to process, careful attention should be paid to the efficiency of the arbitrator function, as it could significantly impact the performance of the model.

It's worth mentioning that using such a mapping system wouldn't replace the need for training a language model on a large corpus of text. Rather, it could be a way of encoding certain pre-defined mappings that the model should adhere to.

These containers would be particularly useful in the realm of theorem proving, network emulation, large language model development, ontology mapping, and any situation where one needs to handle many-to-one or many-to-many relationships based on semantic equivalence. They can vastly simplify the process of mapping varied representations of a concept to a single semantic entity, and managing the complexity of dealing with ambiguous keys.

## Conclusion
The proposed `std::reduction_map` and `std::reduction_multimap` extend the capabilities of `std::map` and `std::multimap` by introducing the concept of semantic equivalence of keys, and can provide an efficient and elegant way to handle complex key-value relationships in a variety of use cases.

Regards, 
Abdul S.
