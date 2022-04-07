//
// Created by Kirill Golubev on 06.04.2022.
//

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include "planet/grid/corner.h"
#include "render/globe_renderer.h"


namespace py = pybind11;

PYBIND11_MODULE(hex_grid, m) {
    py::class_<Globe_renderer>(m, "GlobeRenderer")
            .def(py::init<
                    const std::function<void(float, float, float)> &,
                    const std::function<void(float, float, float)> &,
                    const std::function<void(void)> &,
                    const std::function<void(void)> &,
                    const std::function<void(void)> &,
                    const std::function<void(void)> &,
                    const std::function<void(float, float, float, float, float, float)> &,
                    const std::function<void(void)> &
            >())
            .def("draw_planet", &Globe_renderer::draw_planet);

    py::class_<Planet>(m, "Planet")
            .def(py::init<>())
            .def("divide_grid", [](Planet &p) {
                p.grid = _subdivided_grid(p.grid);
            })
            .def("tile_count", [](Planet &p) {
                return tile_count(p);
            })
            .def("set_grid_size", [](Planet &p, int n) {
                return set_grid_size(p, n);
            })
            .def("init_colours", [](Planet &p) {
                return std::vector<Colour>(tile_count(p));
            });
    py::class_<Colour>(m, "Colour")
            .def(py::init<float, float, float>());
}