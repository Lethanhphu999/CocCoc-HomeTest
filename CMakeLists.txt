cmake_minimum_required(VERSION 3.8)
project(CocCoc VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

add_executable(CocCoc ${HEADERS} ${SOURCES})

target_include_directories(CocCoc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_precompile_headers(CocCoc PRIVATE pch.h)

#set_target_properties(CocCoc PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#)