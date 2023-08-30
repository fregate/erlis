#include <array>
#include <charconv>
#include <cstdint>
#include <fcntl.h>
#include <iomanip>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/un.h>

#include <ei.h>

#include <erlis/ErlIS.h>

#include "ei_new_format.h"

namespace erlis
{

std::vector<std::uint8_t> binary_term(const std::string_view term)
{
	constexpr std::string_view fmt{R"(erl -noinput -eval "io:write(erlang:term_to_binary(%s))." -s init stop)"};
	std::string cmd;

	// it's a kind of magic
	std::stringstream ss;
	ss << std::quoted(term);
	auto quoted_term{std::move(ss.str())}; // there everyting double qouted (from 0 element to the last one)
	*quoted_term.rbegin() = 0; // remove last double qoute
	*quoted_term.begin() = ' '; // remove very first qoute
	// looks like only two addintional allocations if no qouted at all

	cmd.resize(fmt.size() + quoted_term.size());
	std::snprintf(&*cmd.begin(), cmd.size(), fmt.data(), quoted_term.c_str());

	std::array<char, 128> output_buffer;
	std::string output;

	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe)
	{
		throw std::runtime_error("popen() failed!");
	}

	while (fgets(output_buffer.data(), output_buffer.size(), pipe.get()) != nullptr)
	{
		output += output_buffer.data();
	}

	// parse output to vector
	std::vector<std::uint8_t> res;
	res.reserve(output.size() / 2);

	auto c = output.begin();
	auto s = c;
	while (c != output.end())
	{
		if (*c < '0' || *c > '9')
		{
			if (c != s)
			{
				std::uint8_t b;
				const auto [ptr, ec] = std::from_chars(&*s, &*c, b);
				if (ec == std::errc())
					res.push_back(b);
				else if (ec == std::errc::invalid_argument)
					throw std::invalid_argument("invalid data: " + *s);
				else if (ec == std::errc::result_out_of_range)
					throw std::invalid_argument("number larger than uint8: " + *s);

				s = ++c;
			}
			else
			{
				++c;
				++s;
			}
		}
		else
		{
			++c;
		}
	}

	return res;
}

std::vector<std::uint8_t> binary_term2(const std::string_view term)
{
	static const int i = ei_init();
	ei_x_buff buf;
	int res = ei_x_new(&buf);
	res = ei_new_format(&buf, term.data());

	std::vector<std::uint8_t> ret(buf.index, 0);
	std::copy(buf.buff, buf.buff + buf.index, ret.begin());
	ei_x_free(&buf);
	return ret;
}

} // namespace erlis
