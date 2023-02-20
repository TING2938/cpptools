
# cpptools

Provide some useful tools for C++

## how to use this library
```cmake
include(FetchContent)

FetchContent_Declare(
    cpptools
    GIT_REPOSITORY https://github.com/ting2938/cpptools.git 
    GIT_TAG master 
)
FetchContent_MakeAvailable(cpptools)
```

## cmake target
1. `cpptools::ct`: basic target for cpptools
2. `cpptools::gitinfo`: link git infomation to your target:
   ```cmake
   CT_USE_GITINFO()

   add_execuable(your_main main.cpp)
   target_link_libraries(your_main cpptools::gitinfo)
   # and then you can use these macro in main.cpp: 
   #    GIT_BRANCH 
   #    GIT_TAG 
   #    GIT_COMMIT_HASH 
   #    GIT_DIRTY
   ```
3. `cpptools::asan`: asan support for your target

## cmake option

1. `-DCT_ASAN=ON/OFF`: set `ON` to enable link to asan library
