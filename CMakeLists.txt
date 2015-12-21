cmake_minimum_required(VERSION 3.3)
project(machiavelli)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


set(SOURCE_FILES lib/ClientCommand.h main.cpp models/Player.cpp models/Player.hpp lib/Socket.cpp lib/Socket.h lib/Sync_queue.h lib/throw.cpp lib/throw.h controller/GameController.cpp controller/GameController.h models/BaseCard.cpp models/BaseCard.h models/BuildingCard.cpp models/BuildingCard.h models/CharacterCard.cpp models/CharacterCard.h)
add_executable(machiavelli ${SOURCE_FILES} )
