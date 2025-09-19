cmake_minimum_required(VERSION 3.14)
project(Kuramoto_Model LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

include(FetchContent)

FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.2
)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.h)
file(GLOB_RECURSE TEST_SOURCES ${TEST_DIR}/*.cpp)
file(GLOB_RECURSE TEST_HEADERS ${TEST_DIR}/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${CMAKE_SOURCE_DIR}/main.cpp)
add_executable(${PROJECT_NAME}_test ${SOURCES} ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${PROJECT_NAME}_test PRIVATE ${INCLUDE_DIR} ${TEST_DIR})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(${PROJECT_NAME}_test sfml-graphics sfml-window sfml-system sfml-audio)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
set_target_properties(${PROJECT_NAME}_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)