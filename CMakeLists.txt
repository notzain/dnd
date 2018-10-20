cmake_minimum_required(VERSION 3.10)
project(dnd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(dnd
        src/Dungeon.cpp
        src/Dungeon.h
        src/DungeonBossRoom.cpp
        src/DungeonBossRoom.h
        src/DungeonLayer.cpp
        src/DungeonLayer.h
        src/DungeonRoom.cpp
        src/DungeonRoom.h
        src/DungeonStaircase.cpp
        src/DungeonStaircase.h
        src/DungeonVisitable.h
        src/Game.cpp
        src/Game.h
        src/Hero.cpp
        src/Hero.h
        src/Inventory.cpp
        src/Inventory.h
        src/Item.h
        src/Monster.cpp
        src/Monster.h
        src/MonsterReader.cpp
        src/MonsterReader.h
        src/RNG.cpp
        src/RNG.h
        src/main.cpp
        src/FightSystem.cpp
		src/FightSystem.h
		src/InventorySystem.cpp
		src/InventorySystem.h
		src/RustySword.cpp
		src/RustySword.h
		src/KnightSword.cpp 
		src/KnightSword.h
		src/TravelSystem.cpp 
		src/TravelSystem.h
		src/RestSystem.cpp 
		src/RestSystem.h
        src/ExperienceSystem.cpp src/ExperienceSystem.h)