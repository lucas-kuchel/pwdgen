#include "include/appinfo.hpp"
#include "include/generator.hpp"
#include "include/parser.hpp"

#include <vector>

int main(int argc, char** argv) {
    std::vector<std::string_view> args(argv + 1, argv + argc);

    generator::password_state state;

    parser::action_hint action = parser::parse_input(state, args);

    switch (action) {
        case parser::action_hint::generate: {
            generator::generate_password(state);

            if (!state.silent_generate) {
                std::println("avoid sharing your passwords with others");
                std::println("if this password appears too basic (e.g. \"aAbBcC123\") consider regenerating");
                std::println("password score: {:.2f} bits of entropy ({})", state.entropy_bits, generator::rate_strength(state));
            }

            std::println("{}", state.product);

            break;
        }
        case parser::action_hint::version: {
            std::println("pwdgen {}.{}.{}", appinfo::VERSION_MAJOR, appinfo::VERSION_MINOR, appinfo::VERSION_PATCH);

            break;
        }
        case parser::action_hint::terminate: {
            return 1;
        }
    }

    return 0;
}