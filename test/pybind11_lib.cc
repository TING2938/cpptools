#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>

namespace py = pybind11;

py::array_t<int> func(const std::vector<int>& in)
{
    py::array_t<int> ret({(size_t)3, in.size()});
    auto ret_t = ret.mutable_unchecked();
    memset(ret_t.mutable_data(), 0, sizeof(int) * ret.size());
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < in.size(); j++) {
            ret_t(i, j) = in[j] + i;
        }
    }
    return ret;
}

class Student
{
public:
    Student(std::string name) : name(name), age(0) {}

    void setAge(int age)
    {
        this->age = age;
    }

    void setScore(const std::vector<int>& score)
    {
        this->score = score;
    }

    void print()
    {
        std::cout << "Name: " << this->name << "\n"
                  << "Age: " << this->age << "\n"
                  << "Score: ";
        for (auto&& s : this->score) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }

    std::string name;
    int age;
    std::vector<int> score;
};

double calc_mean_score(const Student& s)
{
    return std::accumulate(s.score.begin(), s.score.end(), 0.0) / s.score.size();
}

PYBIND11_MODULE(pybind11_lib, m)
{
    m.def("func", &func, "test for python call cpp");

    py::class_<Student>(m, "Student")
        .def(py::init<std::string>())
        .def("setAge", &Student::setAge)
        .def("setScore", &Student::setScore)
        .def("print", &Student::print)
        .def_readwrite("name", &Student::name)
        .def_readwrite("age", &Student::age)
        .def_readwrite("score", &Student::score);
    m.def("calc_mean_score", &calc_mean_score);
}
