
project(Interfaces)

# No source files for a header-only library

add_library(Interfaces INTERFACE)

# Include directories if needed
target_include_directories(Interfaces INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)