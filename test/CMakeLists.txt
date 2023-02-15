include(fetch_lib)
CT_USE_GITINFO()

set(CT_TEST_LINKED_LIB 
        cpptools::ct
        fmt::fmt 
        gtest
        gtest_main 
        cpptools::gitinfo 
        Eigen3::Eigen
)

file(GLOB CT_TEST_SRC_FILES *.cpp)
foreach(SRC_PATH ${CT_TEST_SRC_FILES})
    get_filename_component(_target ${SRC_PATH} NAME_WE)
    add_executable(${_target} ${SRC_PATH})
    target_link_libraries(${_target} ${CT_TEST_LINKED_LIB})
endforeach()

target_link_libraries(pybind11_tools_test pybind11::embed)

pybind11_add_module(pybind11_lib pybind11_lib.cc)
