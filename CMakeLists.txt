cmake_minimum_required(VERSION 3.2)

project(web_server)

find_package(RapidJSON REQUIRED)

include_directories(
    include
    ${RapidJSON_INCLUDE_DIRS}
)

add_executable(basic_server src/basic/basic_server.cpp)
add_executable(basic_client src/basic/basic_client.cpp)

add_executable(json_server src/json/json_server.cpp)
add_executable(json_client src/json/json_client.cpp)

add_executable(echo_server src/echo/echo_server.cpp)
add_executable(echo_client src/echo/echo_client.cpp)

add_executable(op_server src/operator/op_server.cpp)
add_executable(op_client src/operator/op_client.cpp)

add_executable(uecho_server src/uecho/uecho_server.cpp)
add_executable(uecho_client src/uecho/uecho_client.cpp)

add_executable(gethostbyname src/gethostbyname.cpp)