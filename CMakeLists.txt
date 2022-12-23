cmake_minimum_required(VERSION 3.23)
project(PeterTown)

set(CMAKE_CXX_STANDARD 20)

add_executable(PeterTown main.cpp level.h field.h vector.h field.cpp resource.h resource.cpp level.cpp colony.h lair.h colony.cpp unit.h randomizer.h unit.cpp pathfinder.h pathfinder.cpp controller.cpp controller.h lair.cpp)
