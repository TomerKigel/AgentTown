project(AI_Elements)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(AI_Elements STATIC ${SOURCES})
