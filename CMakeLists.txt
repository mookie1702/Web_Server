cmake_minimum_required(VERSION 3.2)

project(web_server)

# find_package(RapidJSON REQUIRED)

# include_directories(include ${RapidJSON_INCLUDE_DIRS})

# Chapter 1
add_executable(hello_server src/Chap1/hello_server.c)
add_executable(hello_client src/Chap1/hello_client.c)
add_executable(lopen src/Chap1/low_open.c)
add_executable(lread src/Chap1/low_read.c)
add_executable(fds src/Chap1/fd_seri.c)

# Chapter 2
add_executable(tcp_server src/Chap2/tcp_server.c)
add_executable(tcp_client src/Chap2/tcp_client.c)

# Chapter 3
add_executable(endian_conv src/Chap3/endian_conv.c)
add_executable(inet_addr src/Chap3/inet_addr.c)
add_executable(inet_aton src/Chap3/inet_aton.c)
add_executable(inet_ntoa src/Chap3/inet_ntoa.c)

# Chapter 4
add_executable(echo_server src/Chap4/echo_server.c)
add_executable(echo_client src/Chap4/echo_client.c)
add_executable(op_server src/Chap4/op_server.c)
add_executable(op_client src/Chap4/op_client.c)

# Chapter 5
add_executable(uecho_server src/Chap5/uecho_server.c)
add_executable(uecho_client src/Chap5/uecho_client.c)
add_executable(bound_host1 src/Chap5/bound_host1.c)
add_executable(bound_host2 src/Chap5/bound_host2.c)

# Chapter 6
add_executable(file_server src/Chap6/file_server.c)
add_executable(file_client src/Chap6/file_client.c)

# Chapter 7
add_executable(gethostbyname src/Chap7/gethostbyname.c)
add_executable(gethostbyaddr src/Chap7/gethostbyaddr.c)

# Chapter 8
add_executable(sock_type src/Chap8/sock_type.c)
add_executable(get_buf src/Chap8/get_buf.c)
add_executable(set_buf src/Chap8/set_buf.c)

# add_executable(json_server src/json/json_server.cpp)
# add_executable(json_client src/json/json_client.cpp)

# add_executable(echo_mpserver src/echo/echo_mpserv.cpp)
# add_executable(echo_mpclient src/echo/echo_mpclient.cpp)

# add_executable(echo_selectserv src/echo/echo_selectserv.cpp)
# add_executable(select src/common_function/select.cpp)

# Chapter 14
add_executable(news_sender src/Chap14/news_sender.cpp)
add_executable(news_receiver src/Chap14/news_receiver.cpp)
add_executable(news_sender_brd src/Chap14/news_sender_brd.cpp)
add_executable(news_receiver_brd src/Chap14/news_receiver_brd.cpp)
