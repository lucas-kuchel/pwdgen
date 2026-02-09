#pragma once

#include "generator.hpp"

#include <print>
#include <span>

namespace parser {
    enum class next_token_hint {
        none,
        omit,
        length,
    };

    enum class action_hint {
        version,
        generate,
        terminate,
    };

    [[nodiscard]] action_hint parse_input(generator::password_state& state, std::span<std::string_view> args);
}