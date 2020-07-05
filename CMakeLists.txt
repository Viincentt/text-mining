cmake_minimum_required(VERSION 3.0)
project (textmining)
if (NOT CMAKE_BUILD_TYPE)
     set(CMAKE_BUILD_TYPE Release)
endif()
add_compile_options(-pedantic -Werror -Wall -Wextra -std=c++17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -march=native")

file(GLOB TRIE "src/trie/*.cc")
file(GLOB SOURCES_COMPILER "src/compiler/*.cc")
file(GLOB SOURCES_APP "src/app/*.cc")


add_executable(TextMiningCompiler ${TRIE} ${SOURCES_COMPILER})
add_executable(TextMiningApp ${TRIE} ${SOURCES_APP})