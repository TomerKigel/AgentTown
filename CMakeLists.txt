cmake_minimum_required(VERSION 3.12)
project(AgentTown)

set(CMAKE_CXX_STANDARD 20)  # Adjust as needed
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_GENERATOR_TOOLSET "v142")

add_subdirectory(Interfaces)
add_subdirectory(Message_System)
add_subdirectory(AI_Elements)
add_subdirectory(Network_Representation)
add_subdirectory(Server_Communications)
add_subdirectory(Message_Interpreting_System)
add_subdirectory(CAI)

# Add the source files for the Framework_exe
add_executable(Framework_exe
    Framework/Source.cpp  # Add your source files for Framework_exe here
    Framework/Framework.cpp
    Framework/Framework.h
    Framework/Concrete_Mediator.h
)


    #set(BOOST_ROOT "C:/Program Files/boost/boost_1_81_0")
    #set(SFML_DIR "I:/SFML-2.5.1/lib/cmake/SFML")
    set(BOOST_ROOT "D:/a/AgentTown/boost")
    set(SFML_DIR "C:/Program Files (x86)/SFML/./lib/cmake/SFML")


# Include directories for the Framework_exe project
target_include_directories(Framework_exe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/Message_System
    ${CMAKE_CURRENT_SOURCE_DIR}/AI_Elements
    ${CMAKE_CURRENT_SOURCE_DIR}/Message_Interpreting_System
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Representation
    ${CMAKE_CURRENT_SOURCE_DIR}/Server_Communications
    ${CMAKE_CURRENT_SOURCE_DIR}/CAI
)

set(Boost_USE_STATIC_LIBS ON)

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)
find_package(Boost 1.81.0 REQUIRED)

# Link the libraries
target_link_libraries(Framework_exe PRIVATE
    AI_Elements
    Interfaces
    Message_System
    Message_Interpreting_System
    Network_Representation
    Server_Communications
    CAI
    #Boost::system
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
