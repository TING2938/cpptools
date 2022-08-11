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

option(CPPTOOLS_BUILD_TEST "whether to build the test progrom" ON)


add_library(ct_ct INTERFACE)
add_library(ct_eigen INTERFACE)
add_library(ct_spdlog INTERFACE)
add_library(ct_fmt INTERFACE)
add_library(ct_json INTERFACE)
add_library(ct_gtest INTERFACE)
add_library(ct_pybind11 INTERFACE)
add_library(ct_gitinfo INTERFACE)
add_library(ct_all INTERFACE)

add_library(cpptools::ct ALIAS ct_ct)
add_library(cpptools::eigen ALIAS ct_eigen)
add_library(cpptools::spdlog ALIAS ct_spdlog)
add_library(cpptools::fmt ALIAS ct_fmt)
add_library(cpptools::json ALIAS ct_json)
add_library(cpptools::gtest ALIAS ct_gtest)
add_library(cpptools::pybind11 ALIAS ct_pybind11)
add_library(cpptools::gitinfo ALIAS ct_gitinfo)
add_library(cpptools::all ALIAS ct_all)

# fmt
add_subdirectory(third_party/fmt)
target_link_libraries(ct_fmt INTERFACE fmt::fmt-header-only)

# basic
target_include_directories(ct_ct INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(ct_ct INTERFACE ct_fmt)

# spdlog
set(SPDLOG_FMT_EXTERNAL_HO ON CACHE BOOL "") # use external fmt library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/spdlog)
target_link_libraries(ct_spdlog INTERFACE spdlog::spdlog_header_only)

# eigen
set(EIGEN_BUILD_DOC OFF CACHE BOOL "")
set(BUILD_TESTING OFF CACHE BOOL "")
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/eigen)
target_link_libraries(ct_eigen INTERFACE Eigen3::Eigen)

# pybind11
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/pybind11)
target_link_libraries(ct_pybind11 INTERFACE pybind11::embed)

# json
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/json)
target_link_libraries(ct_json INTERFACE nlohmann_json::nlohmann_json)

# gtest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/googletest)
target_link_libraries(ct_gtest INTERFACE gtest gtest_main)

# git info
include(${CMAKE_CURRENT_LIST_DIR}/cmake/git_info.cmake)
target_link_libraries(ct_gitinfo INTERFACE git_info)

# all 
target_link_libraries(ct_all INTERFACE ct_json ct_gtest ct_gitinfo ct_pybind11 ct_eigen ct_spdlog ct_fmt ct_ct)

if (CPPTOOLS_MASTER_PROJECT)
    if (CPPTOOLS_BUILD_TEST)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
    endif()
endif()
