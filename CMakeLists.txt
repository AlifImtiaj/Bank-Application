cmake_minimum_required(VERSION 3.16)

project(BankApp)

find_package(fmt REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather sources
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Use precompiled header
target_precompile_headers(${PROJECT_NAME} PRIVATE include/pch.h)