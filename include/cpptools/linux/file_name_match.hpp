#pragma once

#include <string.h>
#include <string>
#include <vector>

#include <dirent.h>
#include <fnmatch.h>

#include <libgen.h>

namespace ct
{
inline std::vector<std::string> file_match(std::string pattern)
{
#ifdef basename
#undef basename
#endif
    char file_name[1024] = {0};
    std::copy(pattern.begin(), pattern.end(), file_name);
    file_name[pattern.size()] = '\0';
    auto base_name            = basename(static_cast<const char*>(file_name));
    auto dir_name             = dirname(file_name);
    auto dir                  = opendir(dir_name);
    dirent* entry;
    int ret;

    std::vector<std::string> matched;

    if (dir != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            ret = fnmatch(base_name, entry->d_name, FNM_PATHNAME | FNM_PERIOD);
            if (ret == 0) {
                matched.push_back(std::string(dir_name) + "/" + entry->d_name);
            }
        }
    }
    closedir(dir);
    return matched;
}
}  // namespace ct
