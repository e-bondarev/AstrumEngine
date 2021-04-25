cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME        AstrumEngine)
set(PROJECT_VERSION     0.0.1)
set(TARGET_NAME         ${PROJECT_NAME})
set(CMAKE_CXX_FLAGS     /std:c++17)

include(cmake/external_settings.cmake)

project(${TARGET_NAME} VERSION ${PROJECT_VERSION})

file(GLOB SRC 
    src/*.cpp 
    src/**/*.cpp 
    src/**/**/*.cpp 
    src/**/**/**/*.cpp)

add_executable(${TARGET_NAME} ${SRC})
target_include_directories(${TARGET_NAME} PUBLIC src)
target_precompile_headers(${TARGET_NAME} PUBLIC src/pch.h)

add_subdirectory(external/glew/build/cmake)
add_subdirectory(external/glfw)

target_link_libraries(${TARGET_NAME} glew_s)
target_link_libraries(${TARGET_NAME} glfw)

target_include_directories(${TARGET_NAME} PUBLIC external/glew/include)
target_include_directories(${TARGET_NAME} PUBLIC external/glfw/include)