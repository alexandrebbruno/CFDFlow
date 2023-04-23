#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Mesh.hpp"

void exportMesh(pybind11::module& m)
{
    pybind11::class_<Mesh>(m, "Mesh")
        .def(pybind11::init<int, int, double, double, double, double, double, double, double>())
        .def("set_initial_contidion", &Mesh::set_initial_contidion)
        .def("add_temperature", &Mesh::add_temperature)
        .def("set_property", &Mesh::set_property)
        .def("get_last_temperature", &Mesh::get_last_temperature)
        .def("get_prescribed_temperature", &Mesh::get_prescribed_temperature)
        .def("get_neighbors", &Mesh::get_neighbors)
        .def("get_coordinates", &Mesh::get_coordinates)
        .def("get_number_of_cells", &Mesh::get_number_of_cells)
        .def("get_property", &Mesh::get_property)
        .def("compute_dx", &Mesh::compute_dx)
        .def("compute_dy", &Mesh::compute_dy)
        .def("compute_dx_between_neighbors", &Mesh::compute_dx_between_neighbors)
        .def("compute_dy_between_neighbors", &Mesh::compute_dy_between_neighbors)
        .def("compute_property_between_neighbors", &Mesh::compute_property_between_neighbors)
        .def("compute_x_cell_center_coordinates", &Mesh::compute_x_cell_center_coordinates)
        .def("compute_y_cell_center_coordinates", &Mesh::compute_y_cell_center_coordinates);
}
