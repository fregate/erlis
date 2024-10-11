#pragma once

#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

namespace erlis
{

std::vector<std::uint8_t> binary_term(const std::string_view term);
std::vector<std::uint8_t> binary_term2(const std::string_view term);

} // namespace erlis
