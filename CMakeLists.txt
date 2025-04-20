cmake_minimum_required(VERSION 3.8)
project(CocCoc-HomeTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_BUILD_TYPE Debug)

option(ENABLE_TEST "Build tests only" OFF)

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

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "CMAKE_BUILD_TYPE: Release")
else()
    message(STATUS "CMAKE_BUILD_TYPE: Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG=1)
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

if(ENABLE_TEST)
    add_subdirectory(THirdParty/gtest)
    enable_testing()
    add_subdirectory(test)
endif()
#set_target_properties(CocCoc PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#)