#include "include/strutils.hpp"

#include <unordered_set>

namespace strutils {
    bool has_all(const std::string& input, const std::string& other) {
        std::unordered_set<char> chars(input.begin(), input.end());

        for (char c : other) {
            if (chars.find(c) == chars.end()) {
                return false;
            }
        }

        return true;
    }

    std::string remove_duplicates(const std::string& input) {
        std::unordered_set<char> seen;
        std::string result;

        for (char c : input) {
            if (seen.insert(c).second) {
                result += c;
            }
        }
        return result;
    }
}