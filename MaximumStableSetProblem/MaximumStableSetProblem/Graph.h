#pragma once
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Edge.h"

class Graph
{
private:
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
	int** adjacencyMatrix;
public:
	Graph();
	~Graph();
	void generateGraph(int n, int p, int rangeWeight);
	void addVertex(Vertex vertex);
	bool addEdge(Vertex* vertex1, Vertex* vertex2);
	bool addEdge(Vertex* vertex1, Vertex* vertex2, double probability);
	bool exists(Edge edge);
	void print();
	std::vector<Vertex> revolveMaximumIndependentSet();
	void generateAdjacencyMatrix();
	void printAdjacencyMatrix();
	bool adjacencyMatrixIsEmpty();
};
