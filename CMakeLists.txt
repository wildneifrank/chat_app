cmake_minimum_required(VERSION 3.28.1)

set(PROJECT_NAME "chat_room")
set(CMAKE_CXX_STANDARD 11)

project(${PROJECT_NAME} LANGUAGES CXX)
add_subdirectory(server)

add_executable(${PROJECT_NAME} server/src/main.cpp)

target_link_libraries(${PROJECT_NAME} server)


