#include <iomanip>
#include <iostream>

#include <erlis/ErlIS.h>

int main(int argc, const char ** argv)
{
	const auto bin = erlis::binary_term(R"(#{a=>1})");
	for (unsigned int b : bin)
	{
		std::cout << b << ",";
	}
	std::cout << "\n";

	return 0;
}
