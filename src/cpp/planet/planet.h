#ifndef planet_h
#define planet_h

#include "grid/grid.h"

class Planet {
public:
	Planet ();
	~Planet ();
	
	Grid* grid;
};

void clear (Planet&);

#endif
