#pragma once

#include <string>

namespace strutils {
    [[nodiscard]] bool has_all(const std::string& input, const std::string& other);
    [[nodiscard]] std::string remove_duplicates(const std::string& input);
}