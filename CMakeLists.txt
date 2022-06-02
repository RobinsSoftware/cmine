cmake_minimum_required(VERSION 3.16)
project(CMine VERSION 0.1.0)

enable_language(C)

include_directories(include)
include_directories(dependencies/json-c/json-c-install/include)

file(GLOB_RECURSE src "src/*.c")

add_executable(cmine-server ${src})

find_package(json-c CONFIG)
target_link_libraries(cmine-server PRIVATE json-c::json-c)
