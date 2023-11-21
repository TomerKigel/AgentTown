project(AI_Elements)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(AI_Elements STATIC ${SOURCES})

set(BOOST_ROOT "/home/runner/work/AgentTown/boost")

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.81.0)


target_include_directories(AI_Elements PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/../Message_System
    ${Boost_INCLUDE_DIRS}
)


target_link_libraries(AI_Elements PRIVATE Interfaces Message_System)
