project(AI_Elements)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(AI_Elements STATIC ${SOURCES})

target_link_libraries(AI_Elements PRIVATE Interfaces Message_System)

target_include_directories(AI_Elements PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/../Message_System
)
