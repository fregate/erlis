#include <iomanip>
#include <iostream>

#include <erlis/ErlIS.h>

int main(int argc, const char ** argv)
{
	constexpr std::string_view data = R"({"ABC", [1,2,3], #{a=>1}})";
	// constexpr std::string_view data = R"(#{a=>1})";

	const auto bin = erlis::binary_term(data);
	for (unsigned int b : bin)
	{
		std::cout << b << ",";
	}
	std::cout << "\n";

	const auto b2 = erlis::binary_term2(data);
	for (unsigned int b : b2)
	{
		std::cout << b << ",";
	}
	std::cout << "\n";

	return 0;
}
