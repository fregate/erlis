#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

namespace erlis
{

std::vector<std::uint8_t> binary_term(const std::string_view term);

} // namespace erlis
