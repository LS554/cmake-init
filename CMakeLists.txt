set(PROJECT_NAME cmake-init)
set(SOURCES
        src/main.c
        src/main.c
        src/libread.c
)

cmake_minimum_required(VERSION 3.20)
project(${PROJECT_NAME} C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME}
        "${SOURCES}"
)
