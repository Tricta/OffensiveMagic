cmake_minimum_required(VERSION 3.22.1)

project("zygiskcode")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create your shared library
add_library(${CMAKE_PROJECT_NAME} SHARED zygiskcode.cpp zygisk.hpp)

# Include Dobby project
add_subdirectory(HookZz)

# Link Dobby library to your project
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE android log dobby)

# Make sure the include paths are set properly (if Dobby doesn't handle it automatically)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/HookZz/include  # Adjust the include directory as needed
)