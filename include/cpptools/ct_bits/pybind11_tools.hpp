#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <string>
#include <tuple>

namespace ct
{
class __attribute__((visibility("hidden"))) Pickler
{
public:
    Pickler(const std::string& fnm, const std::string& flag)
    {
        auto builtins = pybind11::module_::import("builtins");
        this->fid     = builtins.attr("open")(fnm, flag);
        this->pickle  = pybind11::module_::import("pickle");
    }

    ~Pickler()
    {
        this->fid.attr("close")();
    }

    void dump(pybind11::object obj)
    {
        this->pickle.attr("dump")(obj, this->fid);
    }

    pybind11::object load()
    {
        return this->pickle.attr("load")(this->fid);
    }

private:
    pybind11::object fid;
    pybind11::object pickle;
};

template <typename... _Args>
inline std::tuple<pybind11::object, pybind11::tuple> subplots(int nrows, int ncols, _Args&&... __args)
{
    auto plt            = pybind11::module_::import("matplotlib.pyplot");
    pybind11::tuple res = plt.attr("subplots")(nrows, ncols, std::forward<_Args>(__args)...);
    return {res[0], res[1]};
}

template <typename... _Args>
inline std::tuple<pybind11::object, pybind11::object> subplots(_Args&&... __args)
{
    auto plt            = pybind11::module_::import("matplotlib.pyplot");
    pybind11::tuple res = plt.attr("subplots")(std::forward<_Args>(__args)...);
    return {res[0], res[1]};
}

}  // namespace ct