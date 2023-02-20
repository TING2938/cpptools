cmake_minimum_required(VERSION 3.11)

project(cpptools)

# check if ct is being used directly or via add_subdirectory
if(NOT DEFINED CPPTOOLS_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(CPPTOOLS_MASTER_PROJECT ON)
    else()
        set(CPPTOOLS_MASTER_PROJECT OFF)
    endif()
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if(CPPTOOLS_MASTER_PROJECT)
    set(CMAKE_CXX_STANDARD 17)
endif()

set(CT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "" FORCE)
message(STATUS "CT_LIST_DIR: ${CT_LIST_DIR}")

include(cpptools_macro)
include(asan)

add_library(ct_ct INTERFACE)
add_library(cpptools::ct ALIAS ct_ct)

target_include_directories(ct_ct INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

if(CPPTOOLS_MASTER_PROJECT)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
endif()
