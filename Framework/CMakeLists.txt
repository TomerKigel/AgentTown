cmake_minimum_required(VERSION 3.12)
project(Framework_)

# Use GLOB to include all source files in the current directory
file(GLOB SOURCES "*.cpp" "*.h")

add_executable(Framework_ ${SOURCES})