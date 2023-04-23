#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Solver.hpp"


void exportSolver(pybind11::module& m)
{
    pybind11::class_<Solver>(m, "Solver")
        .def(pybind11::init<const Mesh&>())
        .def("compute_time_step", &Solver::compute_time_step)
        .def("solve", &Solver::solve)
        .def("fill_matrix", &Solver::fill_matrix)
        .def("get_A", &Solver::get_A)
        .def("get_B", &Solver::get_B)
        .def("output_last_temperature", &Solver::output_last_temperature);
}
