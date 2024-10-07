#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
#include <utility>

namespace remember {

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


	// 3 ------------------------------------------------------ 3
	// Print std::tuple values
	template<class Tuple, size_t... values>
	void print_tuple(Tuple&& tuple, std::index_sequence<values...>&&) {
		((std::cout << std::get<values>(tuple) << ' '), ...);
	}

	// second example ----------------------
	template<class Tuple, size_t N>
	class tupleprinter {
	public:
		static void print_tuple(const Tuple& tuple_) {
			tupleprinter<Tuple, N - 1>::print_tuple(tuple_);

			std::cout << std::get<N>(tuple_) << ' ';
		}
	};

	template<class Tuple>
	class tupleprinter<Tuple, 0> {
	public:
		static void print_tuple(const Tuple& tuple_) {
			std::cout << std::get<0>(tuple_) << ' ';
		}
	};

	template<class... args>
	void print(const std::tuple<args...>& tuple_) {
		constexpr size_t tuple_size = std::tuple_size_v<std::tuple<args...>>;
		constexpr size_t tuple_index = tuple_size - 1;

		tupleprinter<std::tuple<args...>, tuple_index>::print_tuple(tuple_);
	}
	// second example ----------------------

	// 4 ------------------------------------------------------ 4
	// Print std::integer_sequence, std::index_sequence
	template<typename Type, Type... values>
	void print_sequece(std::integer_sequence<Type, values...>) {
		((std::cout << values << ' '), ...);
	}

}

int main() {
	// 1 ------------------------------------------------------ 1
	std::cout << "1 ------------------------------------------------------ 1\n";
	std::cout << std::boolalpha << remember::is_same_types_v1<float, double, bool, std::string, char*> << '\n';
	std::cout << remember::is_same_types_v1<float, float, float, float> << "\n\n";

	std::cout << remember::is_same_types_v2<float, double, bool, std::string, char*> << '\n';
	std::cout << remember::is_same_types_v2<float, float, float, float> << '\n';


	// 2 ------------------------------------------------------ 2
	std::cout << "\n\n2 ------------------------------------------------------ 2\n";
	std::vector<int> vec;
	vec.reserve(10);

	remember::emplace_back(vec, 23, 5, 6, 323, 777, 655, 9955);

	for (auto&& val : vec)
		std::cout << val << ' ';
	std::cout << '\n';


	// 3 ------------------------------------------------------ 3
	std::cout << "\n\n3 ------------------------------------------------------ 3\n";
	std::tuple<std::string, double, std::string, int, float> tuple{ "begine", 66.99, "middle", 563, 2.5 };

	// 3.1
	constexpr size_t size = std::tuple_size_v<decltype(tuple)>;

	remember::print_tuple(tuple, std::make_index_sequence<size>());
	std::cout << "\n\n";

	// 3.2
	auto lambda = [](auto&&... args) {
		((std::cout << args << ' '), ...);
		};

	std::apply(lambda, tuple);
	std::cout << "\n\n";

	// 3.3
	remember::print(tuple);

	// 4 ------------------------------------------------------ 4
	std::cout << "\n\n4 ------------------------------------------------------ 4\n";
	auto sequence_1 = std::make_integer_sequence<int, 7>();
	std::integer_sequence<unsigned, 65, 3, 6, 87, 2, 81> sequence_2;

	remember::print_sequece(sequence_1);
	std::cout.write("\n\n", 2);
	remember::print_sequece(sequence_2);



	std::cout.write("\n\n", 2);

	return 0;
}