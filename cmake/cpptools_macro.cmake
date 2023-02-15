
# for git info
macro(CT_USE_GITINFO)
    if(NOT TARGET cpptools::gitinfo)
        include(${CT_LIST_DIR}/cmake/git_info.cmake)
        add_library(cpptools::gitinfo ALIAS git_info)
    endif()
endmacro()