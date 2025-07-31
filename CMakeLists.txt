cmake_minimum_required(VERSION 3.10) 
project(sockets-practice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server
	src/tcp_server_driver.cpp
)

add_executable(client
	src/tcp_client_driver.cpp
)

target_include_directories(server PRIVATE include src)
target_include_directories(client PRIVATE include src)

