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

if(CPPTOOLS_MASTER_PROJECT)
    set(CMAKE_CXX_STANDARD 17)
endif()

set(CT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR})

add_library(ct_ct INTERFACE)
add_library(cpptools::ct ALIAS ct_ct)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/fetch_lib.cmake)

target_include_directories(ct_ct INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(ct_ct INTERFACE cpptools::fmt)

if(CPPTOOLS_MASTER_PROJECT)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
endif()
