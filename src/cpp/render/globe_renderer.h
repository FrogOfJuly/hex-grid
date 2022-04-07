//
// Created by Kirill Golubev on 06.04.2022.
//

#ifndef HEX_GRID_GLOBE_RENDERER_H
#define HEX_GRID_GLOBE_RENDERER_H


#include <functional>
#include "../planet/planet.h"
#include "Colour.h"

class Globe_renderer {

    static const int default_size = 600;

    int width = default_size;
    int height = default_size;

    std::function<void(Vector3)> vertex3f;
    std::function<void(Colour)> color3f;
    std::function<void(void)> end;
    std::function<void(void)> begin_GL_TRIAGNLE_FAN;
    std::function<void(void)> enable_GL_CULL_FACE;
    std::function<void(void)> frontFace_GL_CCW;
    std::function<void(void)> loadIdentity;
    std::function<void(float, float, float, float, float, float)> ortho;

    void set_matrix();

    void draw_tile(const Tile &tile, const Colour &color);

public:

    Globe_renderer(
            const std::function<void(float, float, float)> &vertex3f_,
            const std::function<void(float, float, float)> &color3f_,
            const std::function<void(void)> &begin_GL_TRIAGNLE_FAN,
            const std::function<void(void)> &enable_GL_CULL_FACE,
            const std::function<void(void)> &frontFace_GL_CCW,
            const std::function<void(void)> &loadIdentity,
            const std::function<void(float, float, float, float, float, float)> &ortho,
            const std::function<void(void)> &end
    );

    void draw_planet(const Planet &planet, const std::vector<Colour> &colours);

};


#endif //HEX_GRID_GLOBE_RENDERER_H
