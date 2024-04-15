option(CT_ASAN "use asan check for test" OFF)

add_library(ct_asan_lib INTERFACE)
add_library(cpptools::asan ALIAS ct_asan_lib)
if (CT_ASAN)
    target_compile_options(ct_asan_lib INTERFACE -fsanitize=address)
    target_link_libraries(ct_asan_lib INTERFACE -lasan)
endif()
