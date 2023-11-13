project(Server_Communications)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(Server_Communications STATIC ${SOURCES})
