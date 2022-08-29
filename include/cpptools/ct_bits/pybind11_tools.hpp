#include <pybind11/embed.h>
#include <string>

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
}  // namespace ct