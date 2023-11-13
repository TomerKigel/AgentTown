project(Message_System)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(Message_System STATIC ${SOURCES})
