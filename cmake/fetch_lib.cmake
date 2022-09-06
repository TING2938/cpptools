
include(FetchContent)

# URL can be a file or dir
set(CT_FMT_URL https://github.com/fmtlib/fmt/releases/download/8.1.1/fmt-8.1.1.zip CACHE STRING "")
set(CT_SPDLOG_URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz CACHE STRING "")
set(CT_EIGEN_URL https://github.com/TING2938/eigen-mirror/archive/refs/tags/3.4.0.tar.gz CACHE STRING "")
set(CT_PYBIND11_URL https://github.com/pybind/pybind11/archive/refs/tags/v2.10.0.tar.gz CACHE STRING "")
set(CT_JSON_URL https://github.com/nlohmann/json/releases/download/v3.11.1/json.tar.xz CACHE STRING "")
set(CT_GTEST_URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz CACHE STRING "")

if(NOT TARGET fmt::fmt-header-only)
    message(STATUS "cpptools fetch lib fmt")    
    FetchContent_Declare(
        tag_fmt
        URL ${CT_FMT_URL}
    )
    FetchContent_MakeAvailable(tag_fmt)
endif()
add_library(ct_fmt INTERFACE)
add_library(cpptools::fmt ALIAS ct_fmt)
target_link_libraries(ct_fmt INTERFACE fmt::fmt-header-only)

macro(CT_USE_SPDLOG)
    if(NOT TARGET cpptools::spdlog)
        if (NOT TARGET spdlog::spdlog_header_only)
            message(STATUS "cpptools fetch lib spdlog")
            if (TARGET fmt::fmt-header-only)
                set(SPDLOG_FMT_EXTERNAL_HO ON CACHE BOOL "") # use external fmt library
            endif()
            FetchContent_Declare(
                tag_spdlog
                URL ${CT_SPDLOG_URL}
            )
            FetchContent_MakeAvailable(tag_spdlog)
        endif()
        add_library(ct_spdlog INTERFACE)
        add_library(cpptools::spdlog ALIAS ct_spdlog)
        target_link_libraries(ct_spdlog INTERFACE spdlog::spdlog_header_only)
    endif()
endmacro()

macro(CT_USE_EIGEN)
    if(NOT TARGET cpptools::eigen)
        if(NOT TARGET Eigen3::Eigen)
            message(STATUS "cpptools fetch lib eigen")
            set(EIGEN_BUILD_DOC OFF CACHE BOOL "")
            set(BUILD_TESTING OFF CACHE BOOL "")
            set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "")
            FetchContent_Declare(
                tag_eigen
                URL ${CT_EIGEN_URL}
            )
            FetchContent_MakeAvailable(tag_eigen)
        endif()
        add_library(ct_eigen INTERFACE)
        add_library(cpptools::eigen ALIAS ct_eigen)
        target_link_libraries(ct_eigen INTERFACE Eigen3::Eigen)
    endif()
endmacro()

macro(CT_USE_PYBIND11)
    if(NOT TARGET cpptools::pybind11)
        if(NOT TARGET pybind11::embed)
            message(STATUS "cpptools fetch lib pybind11")
            FetchContent_Declare(
                tag_pybind11
                URL ${CT_PYBIND11_URL}
            )
            FetchContent_MakeAvailable(tag_pybind11)
        endif()
        add_library(ct_pybind11 INTERFACE)
        add_library(cpptools::pybind11 ALIAS ct_pybind11)
        target_link_libraries(ct_pybind11 INTERFACE pybind11::embed)
    endif()
endmacro()

macro(CT_USE_JSON)
    if(NOT TARGET cpptools::json)
        if(NOT TARGET nlohmann_json::nlohmann_json)
            message(STATUS "cpptools fetch lib json")
            set(JSON_BuildTests OFF CACHE INTERNAL "")
            set(JSON_Install OFF CACHE INTERNAL "")
            FetchContent_Declare(
                tag_json
                URL ${CT_JSON_URL}
            )
            FetchContent_MakeAvailable(tag_json)
        endif()
        add_library(ct_json INTERFACE)
        add_library(cpptools::json ALIAS ct_json)
        target_link_libraries(ct_json INTERFACE nlohmann_json::nlohmann_json)
    endif()
endmacro()

macro(CT_USE_GTEST)
    if(NOT TARGET cpptools::gtest)
        if(NOT TARGET gtest)
            message(STATUS "cpptools fetch lib gtest")
            set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
            set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
            set(BUILD_GTEST ON CACHE BOOL "" FORCE)
            FetchContent_Declare(
                tag_gtest
                URL ${CT_GTEST_URL}
            )
            FetchContent_MakeAvailable(tag_gtest)
        endif()
        add_library(ct_gtest INTERFACE)
        add_library(cpptools::gtest ALIAS ct_gtest)
        target_link_libraries(ct_gtest INTERFACE gtest gtest_main)
    endif()
endmacro()

macro(CT_USE_GITINFO)
    if(NOT TARGET cpptools::gitinfo)
        if(NOT TARGET git_info)
            include(${CT_LIST_DIR}/cmake/git_info.cmake)
        endif()
        add_library(cpptools::gitinfo ALIAS git_info)
    endif()
endmacro()
