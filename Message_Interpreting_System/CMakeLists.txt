project(Message_Interpreting_System)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(Message_Interpreting_System STATIC ${SOURCES})
