cmake_minimum_required(VERSION 3.10)
project(CAI)
set(CMAKE_CXX_STANDARD 20)  # Adjust as needed
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_GENERATOR_TOOLSET "v142")

set(SFML_DIR "$ENV{GITHUB_WORKSPACE}/sfml_install/usr/local/lib/cmake/SFML")

file(GLOB SOURCES "*.cpp" "*.h"
"Graphics_Engine/*.cpp" "Graphics_Engine/*.h"
"Graphics_Engine/Graphics/*.cpp" "Graphics_Engine/Graphics/*.h"
"Graphics_Engine/Objects/*.cpp" "Graphics_Engine/Objects/*.h"
"Graphics_Engine/Sound/*.cpp" "Graphics_Engine/Sound/*.h"
"Graphics_Engine/Space/*.cpp" "Graphics_Engine/Space/*.h"
"Graphics_Engine/Physics/*.cpp" "Graphics_Engine/Physics/*.h")

add_library(CAI STATIC ${SOURCES})

set(BOOST_ROOT "/home/runner/work/AgentTown/boost")

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.81.0 EXACT)
find_package(SFML 2.5.1 COMPONENTS graphics window system audio REQUIRED)

target_link_libraries(CAI PRIVATE 
Interfaces
Message_System
AI_Elements
Message_Interpreting_System
Network_Representation
Server_Communications
sfml-graphics
sfml-window
sfml-system
sfml-audio)

target_include_directories(CAI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/../Message_System
    ${CMAKE_CURRENT_SOURCE_DIR}/../AI_Elements
    ${CMAKE_CURRENT_SOURCE_DIR}/../Message_Interpreting_System
    ${CMAKE_CURRENT_SOURCE_DIR}/../Network_Representation
    ${CMAKE_CURRENT_SOURCE_DIR}/../Server_Communications
     ${Boost_INCLUDE_DIRS}
)



