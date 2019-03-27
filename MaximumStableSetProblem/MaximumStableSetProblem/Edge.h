#pragma once
#include "Vertex.h"

class Edge
{
private:
	Vertex vertices[2];
public:
	Edge(Vertex sommet1, Vertex sommet2);
	Edge();
	~Edge();
	bool operator==(const Edge& e) const;
	Vertex* getVertices();
};
