cmake_minimum_required(VERSION 3.10)

project(ProjetCPP LANGUAGES CXX)

# Utilise C++17 (change en C++20/23 si tu veux)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dossiers include/
include_directories(include)

# Récupère tous les .cpp du dossier src
file(GLOB SRC_FILES src/*.cpp)

# Crée l'exécutable
add_executable(ProjetCPP ${SRC_FILES})