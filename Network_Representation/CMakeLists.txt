project(Network_Representation)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(Network_Representation STATIC ${SOURCES})
