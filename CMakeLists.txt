cmake_minimum_required(VERSION 3.27)
project(Practica_4_Examen_)

set(CMAKE_CXX_STANDARD 17)

# Incluye los subdirectorios necesarios
add_subdirectory(Player)
add_subdirectory(Enemy)
add_subdirectory(Combat)
add_subdirectory(Utils)

# Indica la ruta de inclusión para los subdirectorios
include_directories(
        ${CMAKE_SOURCE_DIR}/Player
        ${CMAKE_SOURCE_DIR}/Enemy
        ${CMAKE_SOURCE_DIR}/Combat
        ${CMAKE_SOURCE_DIR}/Utils
)

# Define el ejecutable principal y enlázalo con las bibliotecas correspondientes
add_executable(Practica_4_Examen_
        main.cpp
        Character/Character.cpp
        Character/Character.h
)

target_link_libraries(Practica_4_Examen_ Player Enemy Combat Utils)
