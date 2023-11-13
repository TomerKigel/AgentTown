project(Interfaces)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(Interfaces STATIC ${SOURCES})
