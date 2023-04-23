#include <pybind11/pybind11.h>

void exportMesh(pybind11::module& m);
void exportSolver(pybind11::module& m);

PYBIND11_MODULE(PyCFDFlow, m)
{
    exportMesh(m);
    exportSolver(m);
}
    
