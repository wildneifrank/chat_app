cmake_minimum_required(VERSION 3.28.1)

set(PROJECT_NAME "server")
set(CMAKE_CXX_STANDARD 11)
project(${PROJECT_NAME} LANGUAGES CXX)
add_subdirectory(third_party)

# Add the source files
set(SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp"
)

# Add the header files
set(HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/message.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/server.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/user.h"
)

# Add the library
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} httplib nlohmann_json)