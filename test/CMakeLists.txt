
CT_USE_EIGEN()
CT_USE_GTEST()
CT_USE_GITINFO()

set(CT_TEST_LINKED_LIB 
        cpptools::ct 
        cpptools::gtest 
        cpptools::gitinfo 
        cpptools::eigen
)

file(GLOB CT_TEST_SRC_FILES *.cpp)
foreach(SRC_PATH ${CT_TEST_SRC_FILES})
    get_filename_component(_target ${SRC_PATH} NAME_WE)
    add_executable(${_target} ${SRC_PATH})
    target_link_libraries(${_target} ${CT_TEST_LINKED_LIB})
endforeach()

CT_USE_PYBIND11()
target_link_libraries(pybind11_tools_test cpptools::pybind11)