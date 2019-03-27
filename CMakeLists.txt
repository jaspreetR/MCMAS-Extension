cmake_minimum_required(VERSION 3.5.1)
project(abstract_generator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FindPkgConfig)

set(MAIN "src/main.cpp")
file (GLOB_RECURSE SOURCES "src/**/*.cpp" "src/*.cpp")

get_filename_component(ABSOLUTE_MAIN src/main.cpp ABSOLUTE)
list (REMOVE_ITEM SOURCES "${ABSOLUTE_MAIN}")

message (STATUS ${SOURCES})

set(TEST_EXEC "test_exec")
file (GLOB_RECURSE TESTS "test/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(${PROJECT_NAME} ${MAIN} ${SOURCES})
add_executable(${TEST_EXEC} EXCLUDE_FROM_ALL ${TESTS} ${SOURCES})

include_directories(include/)
include_directories(test/include/)

add_custom_target(run COMMAND "./${PROJECT_NAME}" DEPENDS ${PROJECT_NAME})
add_custom_target(check COMMAND ./${TEST_EXEC} DEPENDS ${TEST_EXEC})
