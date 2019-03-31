#pragma once
#include <vector>

class Vertex
{
private:
	int index;
	int degree;
	double weight;

public:
	std::vector<Vertex> neighbors;
	Vertex(int index, double weight);
	Vertex();
	~Vertex();
	bool addNeighbor(Vertex neighbor);
	bool isInNeighbors(Vertex vertex);
	std::vector<Vertex> getNeighbors();
	bool operator==(const Vertex& v) const;
	int getIndex();
	double getRatio();
	int getDegree();
	int getSupport();
};