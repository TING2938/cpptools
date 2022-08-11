cmake_minimum_required(VERSION 3.2)

project(cpptools)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    # set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# check if ct is being used directly or via add_subdirectory
if(NOT DEFINED CPPTOOLS_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(CPPTOOLS_MASTER_PROJECT ON)
    else()
        set(CPPTOOLS_MASTER_PROJECT OFF)
    endif()
endif()

option(USE_LIB_SPDLOG "whether to use spdlog lib" ON)
option(USE_LIB_EIGEN "whether to use eigen lib" ON)
option(USE_LIB_PYBIND11 "whether to use pybind11 lib" ON)
option(USE_LIB_JSON "whether to use json lib" ON)
option(USE_LIB_GTEST "whether to use gtest lib" ON)
option(USE_LIB_GITINFO "whether to use git info lib" ON)
option(CPPTOOLS_BUILD_TEST "whether to build the test progrom" ON)


add_library(cpptools INTERFACE)
add_library(cpptools::cpptools ALIAS cpptools)

add_subdirectory(third_party/fmt)
target_link_libraries(cpptools INTERFACE fmt::fmt-header-only)

if (USE_LIB_SPDLOG)
    set(SPDLOG_FMT_EXTERNAL_HO ON CACHE BOOL "") # use external fmt library
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/spdlog)
    target_link_libraries(cpptools INTERFACE spdlog::spdlog_header_only)
endif()

if (USE_LIB_EIGEN)
    set(EIGEN_BUILD_DOC OFF CACHE BOOL "")
    set(BUILD_TESTING OFF CACHE BOOL "")
    set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/eigen)
    target_link_libraries(cpptools INTERFACE Eigen3::Eigen)
endif()

if (USE_LIB_PYBIND11)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/pybind11)
    target_link_libraries(cpptools INTERFACE pybind11::embed)
endif()

if (USE_LIB_JSON)
    set(JSON_BuildTests OFF CACHE INTERNAL "")
    set(JSON_Install OFF CACHE INTERNAL "")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/json)
    target_link_libraries(cpptools INTERFACE nlohmann_json::nlohmann_json)
endif()

if (USE_LIB_GTEST)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(BUILD_GTEST ON CACHE BOOL "" FORCE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/googletest)
    target_link_libraries(cpptools INTERFACE gtest gtest_main)
endif()

if (USE_LIB_GITINFO)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/git_info.cmake)
    target_link_libraries(cpptools INTERFACE git_info)
endif()

target_include_directories(cpptools INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

if (CPPTOOLS_MASTER_PROJECT)
    if (CPPTOOLS_BUILD_TEST)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
    endif()
endif()
