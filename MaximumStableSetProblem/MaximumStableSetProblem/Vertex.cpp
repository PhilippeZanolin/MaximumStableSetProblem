#include "pch.h"
#include "Vertex.h"

using namespace std;

Vertex::Vertex(int index, double weight)
{
	this->weight = weight;
	this->index = index;
}

Vertex::Vertex()
{
}

Vertex::~Vertex()
{
}
int Vertex::getIndex()
{
	return index;
}
int Vertex::getSupport()
{
	int support = 0;
	for (int i = 0; i < neighbors.size(); i++)
		support += neighbors[i].getDegree();
	return support;
}
int Vertex::getDegree()
{
	return neighbors.size();
}
double Vertex::getRatio()
{
	return getSupport() * getDegree() / weight;
}
vector<Vertex> Vertex::getNeighbors()
{
	return neighbors;
}
bool Vertex::addNeighbor(Vertex neighbor)
{
	if (isInNeighbors(neighbor))
		return false;
	this->neighbors.emplace_back(neighbor);
	degree++;
	return true;
}

bool Vertex::isInNeighbors(Vertex vertex)
{
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i] == vertex)
			return true;
	}
	return false;
}

bool Vertex::operator==(const Vertex & v) const
{
	return index == v.index;
}