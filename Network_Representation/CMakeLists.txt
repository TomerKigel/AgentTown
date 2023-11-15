project(Network_Representation)

add_library(Network_Representation INTERFACE)

target_link_libraries(Network_Representation INTERFACE Interfaces AI_Elements)

target_include_directories(Network_Representation INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/../AI_Elements
)