cmake_minimum_required(VERSION 3.10) 
project(sockets-practice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TCP
	src/tcp_server.cpp
)

target_include_directories(TCP PRIVATE include src)


