cmake_minimum_required(VERSION 3.11)

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

include(${CMAKE_CURRENT_LIST_DIR}/cmake/fetch_lib.cmake)

target_link_libraries(ct_fmt INTERFACE fmt::fmt-header-only)
target_include_directories(ct_ct INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(ct_ct INTERFACE ct_fmt)
target_link_libraries(ct_spdlog INTERFACE spdlog::spdlog_header_only)
target_link_libraries(ct_eigen INTERFACE Eigen3::Eigen)
target_link_libraries(ct_pybind11 INTERFACE pybind11::embed)
target_link_libraries(ct_json INTERFACE nlohmann_json::nlohmann_json)
target_link_libraries(ct_gtest INTERFACE gtest gtest_main)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/git_info.cmake)
target_link_libraries(ct_gitinfo INTERFACE git_info)

# all 
target_link_libraries(ct_all INTERFACE ct_json ct_gtest ct_gitinfo ct_pybind11 ct_eigen ct_spdlog ct_fmt ct_ct)

if (CPPTOOLS_MASTER_PROJECT)
    if (CPPTOOLS_BUILD_TEST)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
    endif()
endif()
