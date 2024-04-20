#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

// 1 ------------------------------------------------------ 1
// Calculates all types that are the same in the template
template<typename... Types>
constexpr bool is_same_types_v1 = sizeof...(Types) ? std::conjunction_v<std::is_same<std::tuple_element_t<0, std::tuple<Types...>>, Types>...> : false;

// fold expression
template<typename... Types>
constexpr bool is_same_types_v2 = sizeof...(Types) ? (std::is_same_v<std::tuple_element_t<0, std::tuple<Types...>>, Types> && ...) : false;


// 2 ------------------------------------------------------ 2
template<typename ... args> // variadic template. Parameter pack.
void emplace_back(std::vector<typename std::common_type<args...>::type>& vec, args... arg) {
	(vec.emplace_back(arg), ...); // fold expression
}


int main() {
	// 1 ------------------------------------------------------ 1
	std::cout << std::boolalpha << is_same_types_v1<float, double, bool, std::string, char*> << '\n';
	std::cout << is_same_types_v1<float, float, float, float> << "\n\n";

	std::cout << is_same_types_v2<float, double, bool, std::string, char*> << '\n';
	std::cout << is_same_types_v2<float, float, float, float> << '\n';


	// 2 ------------------------------------------------------ 2
	std::vector<int> vec;
	vec.reserve(10);

	emplace_back(vec, 23, 5, 6, 323, 777, 655, 9955);

	std::cout << '\n';
	for (auto&& val : vec)
		std::cout << val << ' ';
	std::cout << '\n';


	return 0;
}