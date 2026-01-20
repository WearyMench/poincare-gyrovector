#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "poincare/poincare.h"
#include "poincare/version.h"

namespace py = pybind11;
using namespace poincare;

PYBIND11_MODULE(poincare_gyrovector_py, m) {
    m.doc() = "Poincaré Ball Gyrovector Algebra Library";
    
    // Version information
    m.attr("__version__") = POINCARE_GYROVECTOR_VERSION_STRING;
    m.def("get_version", &get_version_string, "Get the library version string");
    m.def("get_version_major", &get_version_major, "Get the major version number");
    m.def("get_version_minor", &get_version_minor, "Get the minor version number");
    m.def("get_version_patch", &get_version_patch, "Get the patch version number");

    m.def("mobius_add", &mobius_add,
          "Perform Möbius addition on the Poincaré ball",
          py::arg("x"), py::arg("y"));

    m.def("mobius_scalar_multiply", &mobius_scalar_multiply,
          "Perform Möbius scalar multiplication",
          py::arg("r"), py::arg("x"));

    m.def("exp_map", &exp_map,
          "Compute the exponential map at point x",
          py::arg("x"), py::arg("v"));

    m.def("log_map", &log_map,
          "Compute the logarithmic map at point x",
          py::arg("x"), py::arg("y"));

    m.def("distance", &distance,
          "Compute the distance between two points on the Poincaré ball",
          py::arg("x"), py::arg("y"));

    m.def("norm", &norm,
          "Compute the Euclidean norm of a vector",
          py::arg("x"));

    m.def("dot_product", &dot_product,
          "Compute the dot product of two vectors",
          py::arg("x"), py::arg("y"));

    m.def("is_in_ball", &is_in_ball,
          "Check if a vector is in the unit ball",
          py::arg("x"), py::arg("epsilon") = 1e-10);

    m.def("normalize", &normalize,
          "Normalize a vector to have unit norm",
          py::arg("x"));
}
