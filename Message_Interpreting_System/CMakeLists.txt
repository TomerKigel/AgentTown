project(Message_Interpreting_System)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(Message_Interpreting_System INTERFACE)

target_link_libraries(Message_Interpreting_System INTERFACE Interfaces Message_System)

target_include_directories(Message_Interpreting_System INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/../Message_System
)