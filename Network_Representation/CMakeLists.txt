project(Network_Representation)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(Network_Representation STATIC ${SOURCES})

target_link_libraries(Network_Representation PRIVATE Interfaces Message_System AI_Elements)

target_include_directories(Network_Representation PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/../Message_System
    ${CMAKE_CURRENT_SOURCE_DIR}/../AI_Elements
    
)