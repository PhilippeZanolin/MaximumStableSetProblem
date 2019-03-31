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
	void RemoveVertex(Vertex* vertex);
	void RemoveVertex(int index);
	bool addEdge(Vertex* vertex1, Vertex* vertex2);
	bool addEdge(Vertex* vertex1, Vertex* vertex2, double probability);
	bool exists(Edge edge);
	void print();
	std::vector<Vertex> revolveMaximumIndependentSetApproched();
	static std::vector<Vertex> revolveMaximumIndependentSetExact(Graph graph, std::vector<Vertex> currentSet);

	void generateAdjacencyMatrix(std::vector<Vertex> vertices);
	void printAdjacencyMatrix();
	bool adjacencyMatrixIsEmpty(int ** adjacencyCopy, std::vector<Vertex> verticesCopy);
	int indexMaxRatio(std::vector<Vertex> verticesCopy);
	Vertex getMinimalDegreeVertex();
	int getMinimalDegreeIndex();
	int getIndex(int index, Graph graph);
};

