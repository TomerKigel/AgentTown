cmake_minimum_required(VERSION 3.10)
project(AgentTown)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_GENERATOR_TOOLSET "v142")
set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std=c++20")
set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std=c++20")

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
sET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

#if(WIN32)
#    set(CMAKE_C_COMPILER "cl.exe")
#    set(CMAKE_CXX_COMPILER "cl.exe")
#else()
#   set(CMAKE_C_COMPILER "/usr/bin/gcc")
#   set(CMAKE_CXX_COMPILER "/usr/bin/g++")
#endif()

add_subdirectory(Interfaces)
add_subdirectory(Message_System)
add_subdirectory(AI_Elements)
add_subdirectory(Network_Representation)
add_subdirectory(Server_Communications)
add_subdirectory(Message_Interpreting_System)
add_subdirectory(CAI)

# Add the source files for the Framework_exe
add_executable(Framework_exe
    Framework/Source.cpp
    Framework/Framework.cpp
    Framework/Framework.h
    Framework/Concrete_Mediator.h
)

set(BOOST_ROOT "/home/vboxuser/Desktop/boost_1_81_0")
set(SFML_DIR "/home/vboxuser/Desktop/SFML-2.5.1/lib/cmake/SFML")

# Include directories for the Framework_exe project
target_include_directories(Framework_exe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/Message_System
    ${CMAKE_CURRENT_SOURCE_DIR}/AI_Elements
    ${CMAKE_CURRENT_SOURCE_DIR}/Message_Interpreting_System
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Representation
    ${CMAKE_CURRENT_SOURCE_DIR}/Server_Communications
    ${CMAKE_CURRENT_SOURCE_DIR}/CAI
    ${Boost_INCLUDE_DIRS}
)

set(Boost_USE_STATIC_LIBS ON)

find_package(SFML 2.5.1 COMPONENTS graphics window system audio REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# Link the libraries
target_link_libraries(Framework_exe PRIVATE
    AI_Elements
    Interfaces
    Message_System
    Message_Interpreting_System
    Network_Representation
    Server_Communications
    CAI
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)