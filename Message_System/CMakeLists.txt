project(Message_System)


add_library(Message_System INTERFACE)


set(Boost_DEBUG 1)
set(BOOST_ROOT "/home/runner/work/AgentTown/boost")

set(Boost_USE_STATIC_LIBS ON)

target_include_directories(Message_System INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

find_package(Boost 1.81.0 EXACT)

target_link_libraries(Message_System INTERFACE)#Boost::system)

