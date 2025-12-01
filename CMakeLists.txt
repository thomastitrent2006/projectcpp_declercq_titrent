cmake_minimum_required(VERSION 3.16)
project(ProjetCPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProjetCPP src/main.cpp "include/Avion.h" "include/Trajectoire.h" "include/Piste.h" "include/PositionParking.h" "include/CCR.h" "include/TWR.h" "include/ZoneControle.h" "src/Poisiton3D.cpp" "src/Piste.cpp" "src/Aeroport.cpp" "src/CCR.cpp" "src/APP.cpp" "src/TWR.cpp" "src/DonneesPartagees.cpp" "include/Message.h")

target_include_directories(ProjetCPP PRIVATE
    ${CMAKE_SOURCE_DIR}/SFML/include
)

target_link_directories(ProjetCPP PRIVATE
    ${CMAKE_SOURCE_DIR}/SFML/lib
)

target_link_libraries(ProjetCPP PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)