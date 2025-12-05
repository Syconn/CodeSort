cmake_minimum_required(VERSION 4.0)
project(220FinalMyVersion)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(220FinalMyVersion
        src/main.cpp
        src/structures/ArrayManager.cpp
        src/elements/Card.cpp
        src/server/WinServer.cpp
        src/elements/Game.cpp
        src/structures/Deck.cpp
        src/server/WebRequests.cpp
)

# Link Winsock
target_link_libraries(220FinalMyVersion ws2_32)