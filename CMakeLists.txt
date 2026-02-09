cmake_minimum_required(VERSION 3.21)

project(PasswordGenerator LANGUAGES CXX)

add_executable(pwdgen)

target_include_directories(pwdgen PRIVATE
    "src/include"
)

target_sources(pwdgen PRIVATE
    "src/main.cpp"
    "src/generator.cpp"
    "src/strutils.cpp"
    "src/parser.cpp"
)

set_target_properties(pwdgen PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

install(TARGETS pwdgen
    RUNTIME DESTINATION bin
)
