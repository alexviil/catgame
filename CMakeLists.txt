cmake_minimum_required(VERSION 3.15)
project(catGame)

set(CMAKE_CXX_STANDARD 20)
set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")

file(GLOB SFML_REQUIRED_DLL "libs/SFML-2.5.1/bin/*.dll")
file(COPY ${SFML_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(SFML 2.5.1 COMPONENTS audio network graphics window system REQUIRED)

add_executable(catGame main.cpp src/game.cpp)

target_link_libraries(catGame sfml-audio sfml-network sfml-graphics sfml-window sfml-system)