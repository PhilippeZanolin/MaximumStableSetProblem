#include "pch.h"
#include <iostream>
#include "Graph.h"

int main()
{
	std::cout << "Hello World!\n";
	Graph graph = Graph();
	//Vertex v1 = Vertex(1, 2);
	//Vertex v2 = Vertex(2, 1);
	//Vertex v3 = Vertex(3, 4);
	//graph.addVertex(v1);
	//graph.addVertex(v2);
	//graph.addVertex(v3);
	//graph.addEdge(&v1, &v2);
	graph.generateGraph(5, 0.2, 40);
	graph.print();
	//graph.generateAdjacencyMatrix();
	//graph.printAdjacencyMatrix();
}
