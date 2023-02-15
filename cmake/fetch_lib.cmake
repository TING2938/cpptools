include(FetchContent)

# fmt
FetchContent_Declare(
    fmt
    URL https://github.com/fmtlib/fmt/releases/download/8.1.1/fmt-8.1.1.zip
)
FetchContent_MakeAvailable(fmt)

# eigen
set(EIGEN_BUILD_DOC OFF CACHE BOOL "")
set(BUILD_TESTING OFF CACHE BOOL "")
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "")
FetchContent_Declare(
    eigen
    URL https://github.com/TING2938/eigen-mirror/archive/refs/tags/3.4.0.tar.gz
)
FetchContent_MakeAvailable(eigen)

# pybind11
FetchContent_Declare(
    pybind11
    URL https://github.com/pybind/pybind11/archive/refs/tags/v2.10.0.tar.gz
)
FetchContent_MakeAvailable(pybind11)

# gtest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    gtest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
)
FetchContent_MakeAvailable(gtest)
