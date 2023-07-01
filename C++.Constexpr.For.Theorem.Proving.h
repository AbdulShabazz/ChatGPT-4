/* constexpr allows the developer to check if a condition is true or false at compile time, */
if constexpr (requires (T obj, T::value_type v){ obj.push_back(v); }) {
	// do something
}
/* I would like to extend this functinality to construct a theorem prover which extends C++ to, for example, the following: */
if constexpr (requires (T inobj, Z outobj){ outobj ... inobj; }) {
	// do something
}
/* which states if the type T can be transformed into the type Z, then do something. I would also like add this prover to the Boost library. */
