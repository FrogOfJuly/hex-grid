#include <iostream>
#include "planet/planet.h"
#include "planet/grid/grid.h"

int main() {
    auto *p = new Planet();
    set_grid_size(*p, 10);
    std::cout << "Total tiles: " << tile_count(*p);
    return 0;
}
