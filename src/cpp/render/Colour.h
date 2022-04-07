//
// Created by Kirill Golubev on 06.04.2022.
//

#ifndef HEX_GRID_COLOUR_H
#define HEX_GRID_COLOUR_H

class Colour {
public:
    Colour () :
            r (1), g (1), b (1) {}

    Colour (float rv, float gv, float bv) :
            r (rv), g (gv), b (bv) {}

    Colour& operator = (const Colour& c) {
        r = c.r;
        g = c.g;
        b = c.b;
        return *this;
    }

    float r;
    float g;
    float b;
};

#endif //HEX_GRID_COLOUR_H
