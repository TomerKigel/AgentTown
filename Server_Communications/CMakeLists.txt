project(Server_Communications)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(Server_Communications STATIC ${SOURCES})

set(Boost_USE_STATIC_LIBS ON)

  set(BOOST_ROOT "D:/a/AgentTown/boost")

target_include_directories(Server_Communications PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/../Message_System
)

find_package(Boost 1.81.0 REQUIRED)

target_link_libraries(Server_Communications PRIVATE Interfaces Message_System Boost::system)


