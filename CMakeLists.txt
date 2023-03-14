cmake_minimum_required(VERSION 3.2)

project(web_server)

find_package(RapidJSON REQUIRED)

include_directories(
    include
    ${RapidJSON_INCLUDE_DIRS}
)

add_executable(server
    src/server.cpp
)

add_executable(client
    src/client.cpp
)
