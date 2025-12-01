cmake_minimum_required(VERSION 3.16)
project(ProjetCPP)

set(CMAKE_CXX_STANDARD 20)

# Récupère tous les fichiers source .cpp dans src/
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(ProjetCPP ${PROJECT_SOURCES})

target_include_directories(ProjetCPP PRIVATE
    ${CMAKE_SOURCE_DIR}/include
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

# (Optionnel) Copier automatiquement les DLL SFML à côté de l'exécutable pour Windows
if(WIN32)
    add_custom_command(TARGET ProjetCPP POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/SFML/bin"
        $<TARGET_FILE_DIR:ProjetCPP>
    )
endif()
