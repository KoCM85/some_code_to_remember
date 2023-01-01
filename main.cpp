#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

// Calculates all types that are the same in the template

template<typename... Types>
constexpr bool is_same_types_v1 = sizeof...(Types) ? std::conjunction_v<std::is_same<std::tuple_element_t<0, std::tuple<Types...>>, Types>...> : false;

// fold expression
template<typename... Types>
constexpr bool is_same_types_v2 = sizeof...(Types) ? (std::is_same_v<std::tuple_element_t<0, std::tuple<Types...>>, Types> && ...) : false;

int main() {
	std::cout << std::boolalpha << is_same_types_v1<float, double, bool, std::string, char*> << '\n';
	std::cout << is_same_types_v1<float, float, float, float> << "\n\n";

	std::cout << is_same_types_v2<float, double, bool, std::string, char*> << '\n';
	std::cout << is_same_types_v2<float, float, float, float> << '\n';

	return 0;
}