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

	bool const isEmpty(){ return (vertices.size() == 0); }

	void generateGraph(int n, int p, int rangeWeight);
	void addVertex(Vertex vertex);
	void RemoveVertex(Vertex vertex);
	bool addEdge(Vertex* vertex1, Vertex* vertex2);
	bool addEdge(Vertex* vertex1, Vertex* vertex2, double probability);
	bool exists(Edge edge);
	void print();
	std::vector<Vertex> revolveMaximumIndependentSetApproched();
	static std::vector<Vertex> revolveMaximumIndependentSetExact(Graph graph, std::vector<Vertex> currentSet);

	void generateAdjacencyMatrix();
	void printAdjacencyMatrix();
	bool adjacencyMatrixIsEmpty();
	int indexMaxRatio();
	Vertex getMinimalDegreeVertex();
};

