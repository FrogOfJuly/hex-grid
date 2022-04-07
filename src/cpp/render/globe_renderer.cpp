//
// Created by Kirill Golubev on 06.04.2022.
//

#include "globe_renderer.h"
#include <iostream>

Globe_renderer::Globe_renderer(const std::function<void(float, float, float)> &vertex3f_,
                               const std::function<void(float, float, float)> &color3f_,
                               const std::function<void(void)> &begin_GL_TRIAGNLE_FAN,
                               const std::function<void(void)> &enable_GL_CULL_FACE,
                               const std::function<void(void)> &frontFace_GL_CCW,
                               const std::function<void(void)> &loadIdentity,
                               const std::function<void(float, float, float, float, float, float)> &ortho,
                               const std::function<void(void)> &end) : end(end),
                                                                       begin_GL_TRIAGNLE_FAN(
                                                                               begin_GL_TRIAGNLE_FAN),
                                                                       enable_GL_CULL_FACE(
                                                                               enable_GL_CULL_FACE),
                                                                       frontFace_GL_CCW(
                                                                               frontFace_GL_CCW),
                                                                       loadIdentity(
                                                                               loadIdentity),
                                                                       ortho(ortho) {
    vertex3f = [vertex3f_](const Vector3 &c) {
        return vertex3f_(c.x, c.y, c.z);
    };
    color3f = [color3f_](const Colour &c) {
        return color3f_(c.r, c.g, c.b);
    };
}

void Globe_renderer::set_matrix() {
    loadIdentity();
    double x = (float) width / (float) default_size;
    double y = (float) height / (float) default_size;
    ortho(x, -x, -y, y, -2.0, 2.0);
}

void Globe_renderer::draw_tile(const Tile &tile, const Colour &color) {
//    std::cout << "drawing tile" << std::endl;
    color3f(color);
    begin_GL_TRIAGNLE_FAN();
    vertex3f(vector(tile));
    for (const Corner *c: corners(tile))
        vertex3f(vector(c));
    vertex3f(vector(corners(tile)[0]));
    end();
//    std::cout << "tile drawn" << std::endl;
}

//void Globe_renderer::draw_planet(const Planet &planet, const std::vector<Colour> &colours) {
//    std::vector<Vector3> vertices = std::vector{
//            Vector3(1, -1, -1),
//            Vector3(1, 1, -1),
//            Vector3(-1, 1, -1),
//            Vector3(-1, -1, -1),
//            Vector3(1, -1, 1),
//            Vector3(1, 1, 1),
//            Vector3(-1, -1, 1),
//            Vector3(-1, 1, 1)
//    };
//    std::vector<Vector2> edges = std::vector{
//            Vector2(0, 1),
//            Vector2(0, 3),
//            Vector2(0, 4),
//            Vector2(2, 1),
//            Vector2(2, 3),
//            Vector2(2, 7),
//            Vector2(6, 3),
//            Vector2(6, 4),
//            Vector2(6, 7),
//            Vector2(5, 1),
//            Vector2(5, 4),
//            Vector2(5, 7)
//    };
//    begin_GL_TRIAGNLE_FAN();
//    for (auto edge: edges) {
//        vertex3f(vertices[0]);
//        vertex3f(vertices[1]);
//    }
//    end();
//}

void Globe_renderer::draw_planet(const Planet &planet, const std::vector<Colour> &colours) {
    //    std::cout << "-----drawing planet" << std::endl;
//    set_matrix();
    enable_GL_CULL_FACE();
    frontFace_GL_CCW();
    for (auto &t: tiles(planet)) {
        draw_tile(t, colours[id(t)]);
    }
//    std::cout << ">>>>> planet drawn" << std::endl;
}
