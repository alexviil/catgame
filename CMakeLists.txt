cmake_minimum_required(VERSION 3.15)
project(catGame)

set(CMAKE_CXX_STANDARD 20)
set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")

file(GLOB SFML_REQUIRED_DLL "libs/SFML-2.5.1/bin/*.dll")
file(COPY ${SFML_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(SFML 2.5.1 COMPONENTS audio network graphics window system REQUIRED)

add_executable(catGame
        main.cpp
        src/main/game.cpp
        src/main/world/world.cpp
        src/main/world/world.h
        src/main/world/tile.cpp
        src/main/world/tile.h
        src/constants.h
        src/main/draw.cpp
        src/main/draw.h
        src/main/actor/actor.cpp
        src/main/actor/actor.h
        src/main/actor/player.cpp
        src/main/actor/player.h
        src/main/textureManager.cpp
        src/main/textureManager.h
        src/main/actor/actorManager.cpp
        src/main/actor/actorManager.h src/main/actor/textContainer.h src/main/headUpDisplay/cursor.cpp src/main/headUpDisplay/cursor.h src/main/headUpDisplay/overlay.cpp src/main/headUpDisplay/overlay.h)

target_link_libraries(catGame sfml-audio sfml-network sfml-graphics sfml-window sfml-system)