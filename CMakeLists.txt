cmake_minimum_required(VERSION 3.8)
project(CocCoc-HomeTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_BUILD_TYPE Debug)

# Main executable sources
set(SOURCES
    commands/command.cpp
    commands/command_controller.cpp
    data/map.cpp
    core/file_utilities.cpp
    core/application.cpp
    main.cpp
)

set(HEADERS
    commands/command.h
    commands/command_controller.h
    data/map.h
    core/file_utilities.h
    core/application.h
)

# Testing configuration
enable_testing()
add_subdirectory(ThirdParty/gtest)

# Test sources
set(TEST_SOURCES
    data/map_test.cpp
    commands/command_test.cpp
    commands/command_controller_test.cpp
)

# Add test executable
add_executable(${PROJECT_NAME} ${HEADER} ${SOURCES} ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)

# Add test to CTest
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "CMAKE_BUILD_TYPE: Release")
else()
    message(STATUS "CMAKE_BUILD_TYPE: Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG=1)
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

#set_target_properties(CocCoc PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#)