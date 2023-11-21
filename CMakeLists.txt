cmake_minimum_required(VERSION 3.5)

set (PROJECT_NAME System-Tray-For-NordVPN)

project(${PROJECT_NAME} LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


#ensure that cmake won't be executed in main directory
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "Building in-source is not supported! Create a build directory and remove ${CMAKE_SOUREC_DIR}/CmakeCache.txt")
endif()

set(IS_ROOT_PROJECT OFF)
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_ROOT_PROJECT ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NordVPN.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
