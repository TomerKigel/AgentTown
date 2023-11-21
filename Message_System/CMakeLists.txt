project(Message_System)

# No source files for a header-only library

add_library(Message_System INTERFACE)

# Include directories if needed
target_include_directories(Message_System INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)
set(Boost_DEBUG 1)
set(Boost_ROOT "/home/runner/work/AgentTown/boost")
#set(BOOST_ROOT "C:/Program Files/boost/boost_1_81_0")

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(Message_System INTERFACE)#Boost::system)

