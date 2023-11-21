project(Network_Representation)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(Network_Representation STATIC ${SOURCES})

target_include_directories(Network_Representation PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/../Message_System
    ${CMAKE_CURRENT_SOURCE_DIR}/../AI_Elements
)

set(BOOST_ROOT "/home/runner/work/AgentTown/boost")

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.81.0 EXACT REQUIRED COMPONENTS lexical_cast)

target_link_libraries(Network_Representation PRIVATE Interfaces Message_System AI_Elements Boost::lexical_cast)

