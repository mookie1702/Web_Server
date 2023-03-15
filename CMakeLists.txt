cmake_minimum_required(VERSION 3.2)

project(web_server)

find_package(RapidJSON REQUIRED)

include_directories(
    include
    ${RapidJSON_INCLUDE_DIRS}
)

add_executable(basic_server src/basic_server.cpp)
add_executable(basic_client src/basic_client.cpp)

add_executable(json_server src/json_server.cpp)
add_executable(json_client src/json_client.cpp)

add_executable(echo_server src/echo_server.cpp)
add_executable(echo_client src/echo_client.cpp)

add_executable(op_server src/op_server.cpp)
add_executable(op_client src/op_client.cpp)