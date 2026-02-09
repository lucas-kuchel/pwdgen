#include "include/parser.hpp"
#include "include/charsets.hpp"
#include "include/generator.hpp"
#include "include/strutils.hpp"

#include <print>
#include <span>
#include <string>

namespace parser {
    action_hint parse_input(generator::password_state& state, std::span<std::string_view> args) {
        next_token_hint hint = next_token_hint::none;

        if (args.size() == 0) {
            return action_hint::version;
        }

        if (args.size() == 1) {
            std::string_view arg = args.back();

            if (arg == "-v" || arg == "--version") {
                return action_hint::version;
            }
        }

        for (auto arg : args) {
            if (hint == next_token_hint::length) {
                if (state.length == 0) {
                    state.length = std::stoi(arg.data());
                }

                hint = next_token_hint::none;
            }
            else if (hint == next_token_hint::omit) {
                state.omitted = arg;
                hint = next_token_hint::none;
            }
            else if (arg == "-q" || arg == "--quiet") {
                state.silent_generate = true;
            }
            else if (arg == "--omit") {
                hint = next_token_hint::omit;
            }
            else if (arg == "-l" || arg == "--length") {
                hint = next_token_hint::length;
            }
            else if (arg == "--omit-numbers") {
                state.omitted += charsets::NUMBERS;
            }
            else if (arg == "--omit-uppercase") {
                state.omitted += charsets::UPPERCASE;
            }
            else if (arg == "--omit-lowercase") {
                state.omitted += charsets::LOWERCASE;
            }
            else if (arg == "--omit-symbols") {
                state.omitted += charsets::SYMBOLS;
            }
            else {
                std::println("error: unrecognised argument: {}", arg);

                return action_hint::terminate;
            }
        }

        if (state.length == 0) {
            std::println("error: password length must be greater than zero");

            return action_hint::terminate;
        }

        state.omitted = strutils::remove_duplicates(state.omitted);

        if (strutils::has_all(state.omitted, charsets::LOWERCASE) && strutils::has_all(state.omitted, charsets::UPPERCASE) &&
            strutils::has_all(state.omitted, charsets::NUMBERS) && strutils::has_all(state.omitted, charsets::SYMBOLS)) {
            std::println("error: all supported characters omitted; cannot create password");

            return action_hint::terminate;
        }

        return action_hint::generate;
    }
}