#include "include/generator.hpp"
#include "include/charsets.hpp"
#include "include/strutils.hpp"

#include <algorithm>
#include <random>

namespace generator {
    void generate_password(password_state& state) {
        state.product.clear();

        std::string lower = strutils::remove_duplicates(charsets::LOWERCASE);
        std::string upper = strutils::remove_duplicates(charsets::UPPERCASE);
        std::string numbers = strutils::remove_duplicates(charsets::NUMBERS);
        std::string symbols = strutils::remove_duplicates(charsets::SYMBOLS);

        for (char c : state.omitted) {
            lower.erase(std::remove(lower.begin(), lower.end(), c), lower.end());
            upper.erase(std::remove(upper.begin(), upper.end(), c), upper.end());
            numbers.erase(std::remove(numbers.begin(), numbers.end(), c), numbers.end());
            symbols.erase(std::remove(symbols.begin(), symbols.end(), c), symbols.end());
        }

        std::string full_pool = lower + upper + numbers + symbols;

        std::random_device rd;
        std::mt19937 gen(rd());

        auto random_char = [&gen](const std::string& pool) {
            std::uniform_int_distribution<> dis(0, pool.size() - 1);

            return pool[dis(gen)];
        };

        if (!lower.empty()) {
            state.product += random_char(lower);
        }

        if (!upper.empty()) {
            state.product += random_char(upper);
        }

        if (!numbers.empty()) {
            state.product += random_char(numbers);
        }

        if (!symbols.empty()) {
            state.product += random_char(symbols);
        }

        while (state.product.size() < state.length) {
            state.product += random_char(full_pool);
        }

        std::shuffle(state.product.begin(), state.product.end(), gen);
    }
}