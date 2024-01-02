cmake_minimum_required(VERSION 3.12)
project(Framework_exe)

# Use GLOB to include all source files in the current directory
file(GLOB SOURCES "*.cpp" "*.h")

add_executable(Framework_exe ${SOURCES})

target_include_directories(Framework_exe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/AI_Elements
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/Message_System
    ${CMAKE_CURRENT_SOURCE_DIR}/Message_Interpreting_System
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Representation
    ${CMAKE_CURRENT_SOURCE_DIR}/Server_Communications
    ${CMAKE_CURRENT_SOURCE_DIR}/CAI
)

target_link_libraries(Framework_exe PRIVATE
    AI_Elements
    Interfaces
    Message_System
    Message_Interpreting_System
    Network_Representation
    Server_Communications
    CAI
    boost_log
)
