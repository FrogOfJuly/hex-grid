#include "tile.h"
#include "corner.h"

Tile::Tile (int i, int e) :
	id (i), edge_count (e) {
	tiles.resize(edge_count, nullptr);
	corners.resize(edge_count, nullptr);
	edges.resize(edge_count, nullptr);
}

int position (const Tile& t, const Tile* n) {
	for (int i=0; i<t.edge_count; i++)
		if (t.tiles[i] == n)
			return i;
	return -1;
}

int position (const Tile& t, const Corner* c) {
	for (int i=0; i<t.edge_count; i++)
		if (t.corners[i] == c)
			return i;
	return -1;
}

int position (const Tile& t, const Edge* e) {
	for (int i=0; i<t.edge_count; i++)
		if (t.edges[i] == e)
			return i;
	return -1;
}

int id (const Tile& t) {return t.id;}
int edge_count (const Tile& t) {return t.edge_count;}
const Vector3& vector (const Tile& t) {return t.v;}
const std::vector<const Tile*>& tiles (const Tile& t) {return t.tiles;}
const std::vector<const Corner*>& corners (const Tile& t) {return t.corners;}
const std::vector<const Edge*>& edges (const Tile& t) {return t.edges;}

const Tile* nth_tile (const Tile& t, int n) {
	int k = n < 0 ?
		n % edge_count(t) + edge_count(t) :
		n % edge_count(t);
	return t.tiles[k];
}

const Corner* nth_corner (const Tile& t, int n) {
	int k = n < 0 ?
		n % edge_count(t) + edge_count(t) :
		n % edge_count(t);
	return t.corners[k];
}

const Edge* nth_edge (const Tile& t, int n) {
	int k = n < 0 ?
		n % edge_count(t) + edge_count(t) :
		n % edge_count(t);
	return t.edges[k];
}
