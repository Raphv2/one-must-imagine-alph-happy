cmake_minimum_required(VERSION 3.10)

# set the project name
project(OMIAH)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# gkit files
file(GLOB gkit_files "src/gKit/*.cpp")
file(GLOB files "src/src/*.cpp")

# Création de l'exécutable
add_executable(${PROJECT_NAME} ${gkit_files} ${files})

# Spécification du répertoire de sortie pour l'exécutable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

target_include_directories(${PROJECT_NAME} PUBLIC "src/gKit")
target_include_directories(${PROJECT_NAME} PUBLIC "./inc")
target_link_libraries(${PROJECT_NAME} GL GLEW SDL2 SDL2_image)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Ajouter une cible personnalisée pour la génération de la documentation
add_custom_target(
    documentation
    COMMAND doxygen ${CMAKE_SOURCE_DIR}/doc/Doxyfile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating documentation with Doxygen"
    VERBATIM
)

# Ajouter la cible de documentation comme dépendance
add_dependencies(${PROJECT_NAME} documentation)
