cmake_minimum_required(VERSION 3.3)
project(machiavelli)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES ClientCommand.h main.cpp Player.cpp Player.hpp Socket.cpp Socket.h Sync_queue.h throw.cpp throw.h)
add_executable(machiavelli ${SOURCE_FILES} )
