#include "pch.h"
#include "Edge.h"

Edge::Edge(Vertex vertex1, Vertex vertex2)
{
	vertices[0] = vertex1;
	vertices[1] = vertex2;
}

Edge::Edge()
{
}


Edge::~Edge()
{
}

Vertex* Edge::getVertices()
{
	return vertices;
}

bool Edge::operator==(const Edge & e) const
{
	if (e.vertices[0] == vertices[0] && e.vertices[1] == vertices[1] || e.vertices[0] == vertices[1] && e.vertices[1] == vertices[0])
		return true;
	return false;
}
