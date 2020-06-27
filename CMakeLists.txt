cmake_minimum_required(VERSION 3.0)
project (textmining)


 if (NOT CMAKE_BUILD_TYPE)
     set(CMAKE_BUILD_TYPE Debug)
 endif()
#[[INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})]]
add_compile_options(-pedantic -Werror -Wall -Wextra -std=c++17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -march=native")

file(GLOB TRIE "src/trie/*.cc")
file(GLOB SOURCES_COMPILER "src/compiler/*.cc")
file(GLOB SOURCES_APP "src/app/*.cc")


add_executable(TextMiningCompiler ${TRIE} ${SOURCES_COMPILER})
add_executable(TextMiningApp ${TRIE} ${SOURCES_APP})
#[[
    TARGET_LINK_LIBRARIES(chessengine ${Boost_LIBRARIES}
            dl)
        FIND_PACKAGE(GTest)
    if (GTest_FOUND)
    add_executable(testchess EXCLUDE_FROM_ALL ${SOURCES_TEST} ${SOURCES})
    TARGET_LINK_LIBRARIES(testchess ${Boost_LIBRARIES}
            gtest dl)

    add_custom_target(check
            COMMAND testchess
            DEPENDS testchess
            )
    add_custom_target(pgn
            COMMAND "../src/pgn/tests/testsuit.sh"
            )
    endif()
]]
