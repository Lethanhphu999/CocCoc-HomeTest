cmake_minimum_required(VERSION 3.8)
project(CocCoc VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sources
set(SOURCES
    main.cpp
    Application.cpp
    CommandController.cpp
    Map.cpp
)

set(HEADERS
    Application.h
    CommandController.h
    Map.h
)

# Add executable
add_executable(CocCoc ${SOURCES} ${HEADERS})

# Precompiled header (PCH)
target_precompile_headers(CocCoc PRIVATE pch.h)

# Include directories if needed (optional)
# target_include_directories(CocCoc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set output directory (optional)
#set_target_properties(CocCoc PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#)