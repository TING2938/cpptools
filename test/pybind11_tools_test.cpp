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
