project(Message_System)

# No source files for a header-only library

add_library(Message_System INTERFACE)

  set(BOOST_ROOT "D:/a/AgentTown/boost")

# Include directories if needed
target_include_directories(Message_System INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.81.0 REQUIRED)

target_link_libraries(Message_System INTERFACE)
