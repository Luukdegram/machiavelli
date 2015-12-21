cmake_minimum_required(VERSION 3.3)
project(machiavelli)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


set(SOURCE_FILES lib/ClientCommand.h main.cpp models/Player.cpp models/Player.hpp lib/Socket.cpp lib/Socket.h lib/Sync_queue.h lib/throw.cpp lib/throw.h controller/GameController.cpp controller/GameController.h models/BaseCard.cpp models/BaseCard.h models/BuildingCard.cpp models/BuildingCard.h models/CharacterCard.cpp models/CharacterCard.h models/character_cards/Thief.cpp models/character_cards/Thief.h models/CharacterCardFactory.cpp models/CharacterCardFactory.h models/CharacterType.h models/character_cards/Assassin.cpp models/character_cards/Assassin.h models/character_cards/Magician.cpp models/character_cards/Magician.h models/character_cards/King.cpp models/character_cards/King.h models/character_cards/Preacher.cpp models/character_cards/Preacher.h models/character_cards/Merchant.cpp models/character_cards/Merchant.h models/character_cards/Builder.cpp models/character_cards/Builder.h models/character_cards/Condotierri.cpp models/character_cards/Condotierri.h)
add_executable(machiavelli ${SOURCE_FILES} )
