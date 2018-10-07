cmake_minimum_required(VERSION 3.10)
project(dnd)

set(CMAKE_CXX_STANDARD 14)

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
        )