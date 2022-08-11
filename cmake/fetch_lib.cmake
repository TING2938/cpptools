
include(FetchContent)

message(STATUS "cpptools fetch lib fmt")
FetchContent_Declare(
    tag_fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 8.1.1
)
FetchContent_MakeAvailable(tag_fmt)

message(STATUS "cpptools fetch lib spdlog")
set(SPDLOG_FMT_EXTERNAL_HO ON CACHE BOOL "") # use external fmt library
FetchContent_Declare(
    tag_spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.10.0
)
FetchContent_MakeAvailable(tag_spdlog)

message(STATUS "cpptools fetch lib eigen")
set(EIGEN_BUILD_DOC OFF CACHE BOOL "")
set(BUILD_TESTING OFF CACHE BOOL "")
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "")
FetchContent_Declare(
    tag_eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(tag_eigen)

message(STATUS "cpptools fetch lib pybind11")
FetchContent_Declare(
    tag_pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.9.2
)
FetchContent_MakeAvailable(tag_pybind11)

message(STATUS "cpptools fetch lib json")
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
FetchContent_Declare(
    tag_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.1
)
FetchContent_MakeAvailable(tag_json)

message(STATUS "cpptools fetch lib gtest")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    tag_gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.0
)
FetchContent_MakeAvailable(tag_gtest)

