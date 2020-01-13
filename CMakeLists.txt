cmake_minimum_required(VERSION 3.15)
project(milestone2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(milestone2 TestClientHandler.cpp Solver.h CacheManager.h FileCacheManager.h ClientHandler.h TestClientHandler.h)