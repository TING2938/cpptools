
include(FetchContent)

message(STATUS "cpptools fetch lib fmt")
FetchContent_Declare(
    tag_fmt
    URL https://github.com/fmtlib/fmt/releases/download/8.1.1/fmt-8.1.1.zip
)
FetchContent_MakeAvailable(tag_fmt)

message(STATUS "cpptools fetch lib spdlog")
set(SPDLOG_FMT_EXTERNAL_HO ON CACHE BOOL "") # use external fmt library
FetchContent_Declare(
    tag_spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz
)
FetchContent_MakeAvailable(tag_spdlog)

message(STATUS "cpptools fetch lib eigen")
set(EIGEN_BUILD_DOC OFF CACHE BOOL "")
set(BUILD_TESTING OFF CACHE BOOL "")
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "")
FetchContent_Declare(
    tag_eigen
    URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
)
FetchContent_MakeAvailable(tag_eigen)

message(STATUS "cpptools fetch lib pybind11")
FetchContent_Declare(
    tag_pybind11
    URL https://github.com/pybind/pybind11/archive/refs/tags/v2.10.0.tar.gz
)
FetchContent_MakeAvailable(tag_pybind11)

message(STATUS "cpptools fetch lib json")
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
FetchContent_Declare(
    tag_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.1/json.tar.xz
)
FetchContent_MakeAvailable(tag_json)

message(STATUS "cpptools fetch lib gtest")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    tag_gtest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
)
FetchContent_MakeAvailable(tag_gtest)

