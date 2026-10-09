cmake_minimum_required(VERSION 3.20)

project(TTO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(tto_game src/game.cpp)
target_include_directories(tto_game PUBLIC include)

add_executable(tto src/main.cpp)
target_link_libraries(tto PRIVATE tto_game)

enable_testing()
add_executable(tto_tests tests/game_tests.cpp)
target_link_libraries(tto_tests PRIVATE tto_game)
add_test(NAME tto_tests COMMAND tto_tests)
