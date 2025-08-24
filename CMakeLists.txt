cmake_minimum_required(VERSION 3.16)
project(SCPicker.out LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пусть до raylib, можно переопределить при вызове cmake
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/raylib_external" CACHE PATH "Path to raylib")

# Подключаем include/ и raylib
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${RAYLIB_DIR}
)

# Собираем все cpp из src/
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

# Линкуем raylib и системные либы
target_link_libraries(${PROJECT_NAME}
    raylib
    GL
    m
    pthread
    dl
    rt
    X11
)

# Подсказываем CMake где искать raylib
link_directories(${RAYLIB_DIR})
