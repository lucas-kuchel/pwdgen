#pragma once

#include <string>

namespace generator {
    struct password_state {
        std::string omitted;
        std::string product;
        std::size_t length = 0;
        double entropy_bits = 0.0;
    };

    void generate_password(password_state& state);
    [[nodiscard]] std::string rate_strength(const password_state& state);
}