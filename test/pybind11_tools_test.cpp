#include "cpptools/ct_bits/pybind11_tools.hpp"
#include <gtest/gtest.h>

namespace py = pybind11;
using namespace py::literals;

TEST(ct_test, pickler_test)
{
    py::scoped_interpreter guard;

    {  // dump test
        ct::Pickler p("dump.pk", "wb");
        auto tuple1 = py::make_tuple(1, 2, 4);
        p.dump(tuple1);
        p.dump(py::make_tuple(3, 5, 1));
    }

    {  // load test
        ct::Pickler p("dump.pk", "rb");
        auto tuple1 = p.load();
        auto tuple2 = p.load();
        py::print("tuple1: ", tuple1, ", tuple2: ", tuple2);
    }
}

TEST(ct_test, subplots_test)
{
    py::scoped_interpreter guard;
    auto plt         = py::module_::import("matplotlib.pyplot");
    auto&& [fig, ax] = ct::subplots(2, 1, "figsize"_a = py::make_tuple(10, 8));

    std::vector<int> y = {2, 4, 3};
    ax[0].attr("plot")(y, "--o");
    ax[1].attr("plot")(y, ":o");
    plt.attr("show")();
}