project(Message_System)

# No source files for a header-only library

add_library(Message_System INTERFACE)

if(MSVC)
    set(BOOST_ROOT "C:/Program Files/boost/boost_1_81_0")
else()
    set(BOOST_ROOT "D:\a\AgentTown\boost")
endif()

# Include directories if needed
target_include_directories(Message_System INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    BOOST_ROOT
)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(Message_System INTERFACE
    Boost::system
)