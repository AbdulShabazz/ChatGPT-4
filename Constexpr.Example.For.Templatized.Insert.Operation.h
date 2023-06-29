/* compile-time if (constexpr) example for a templatized insert operation */
void add(auto& coll, const auto& value) {
	//if constexpr (std::is_same_v<decltype(coll), std::vector<int>>) {
	if constexpr(requires { coll.push_back(value); }) {
		coll.push_back(value);
	} else {
		coll.insert(value);
	}
}

/* Example use */
int main() {
	std::vector<int> v;
	std::set<int> s;
	add(v, 42);
	add(s, 42);
}
