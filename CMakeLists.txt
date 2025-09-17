cmake_minimum_required(VERSION 3.14)
project(Kuramoto_Model LANGUAGES CXX)

# Imposta lo standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Organizza le directory
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Includi SFML tramite FetchContent
include(FetchContent)

FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.2
)

FetchContent_MakeAvailable(SFML)

# Aggiungi i file sorgente manualmente per evitare conflitti
set(SOURCES
    ${SRC_DIR}/Analysis.cpp
    ${SRC_DIR}/Graphics.cpp
    ${SRC_DIR}/Kuramoto.cpp
    ${SRC_DIR}/Oscillator.cpp
    ${SRC_DIR}/Simulation.cpp
    ${SRC_DIR}/SimulationPresets.cpp
    ${CMAKE_SOURCE_DIR}/main.cpp
)

# Crea l'eseguibile
add_executable(${PROJECT_NAME} ${SOURCES})

# Includi le directory header
target_include_directories(${PROJECT_NAME}
    PRIVATE ${INCLUDE_DIR}
)

# Collega le librerie SFML
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Opzionale: organizza l'output
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)