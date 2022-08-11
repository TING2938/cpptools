# https://stackoverflow.com/questions/51727566/how-to-make-git-commit-hash-available-in-c-code-without-needless-recompiling
# https://github.com/andrew-hardin/cmake-git-version-tracking

macro(git_run_command _git_command _output)
    execute_process(
        COMMAND bash -c ${_git_command}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE ${_output}
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endmacro()

# Get the current working branch
macro(git_get_branch _git_branch)
    git_run_command("git rev-parse --abbrev-ref HEAD" ${_git_branch})
endmacro()

# Get the tag
macro(git_get_tag _git_tag)
    git_run_command("git describe --tags --always" ${_git_tag})
endmacro()

# Get the latest commit hash
macro(git_get_hash _git_hash)
    git_run_command("git rev-parse HEAD" ${_git_hash})
endmacro()

# check whether current working dir is dirty
macro(git_is_dirty _git_dirty)
    git_run_command("git status --short" _git_dirty_temp)
    if (_git_dirty_temp STREQUAL "")
        set(${_git_dirty} OFF)
    else()
        set(${_git_dirty} ON)
    endif()
endmacro()

git_get_branch(GIT_BRANCH)
git_get_tag(GIT_TAG)
git_get_hash(GIT_COMMIT_HASH)
git_is_dirty(GIT_DIRTY)

add_library(git_info INTERFACE)
# add_library(git_info::git_info ALIAS git_info)

message(STATUS "GIT_BRANCH: ${GIT_BRANCH}")
message(STATUS "GIT_TAG: ${GIT_TAG}")
message(STATUS "GIT_COMMIT_HASH: ${GIT_COMMIT_HASH}")
target_compile_definitions(git_info INTERFACE "-DGIT_BRANCH=\"${GIT_BRANCH}\"")
target_compile_definitions(git_info INTERFACE "-DGIT_TAG=\"${GIT_TAG}\"")
target_compile_definitions(git_info INTERFACE "-DGIT_COMMIT_HASH=\"${GIT_COMMIT_HASH}\"")
if(GIT_DIRTY)
    target_compile_definitions(git_info INTERFACE "-DGIT_DIRTY=1")
    message(WARNING "the git working dir is dirty !!!")
else()
    target_compile_definitions(git_info INTERFACE "-DGIT_DIRTY=0")
endif(GIT_DIRTY)

# add_compile_definitions("GIT_COMMIT_HASH=\"${GIT_COMMIT_HASH}\"")
# add_compile_definitions("GIT_BRANCH=\"${GIT_BRANCH}\"")
# add define in cmake
# target_compile_definitions(${PROJECT_NAME} PRIVATE
#     "-DGIT_COMMIT_HASH=\"${GIT_COMMIT_HASH}\"")
# 
# and then in c++ file:
# #ifndef GIT_COMMIT_HASH
# #define GIT_COMMIT_HASH "?"
# #endif
#