#include "pch.h"
#include <iostream>
#include "Graph.h"

void approximativeResolution(Graph graph)
{
	std::vector<Vertex> mwis = graph.revolveMaximumIndependentSet();
	for (int i = 0; i < mwis.size(); i++)
	{
		std::cout << "index:" << mwis[i].getIndex() << "\n";
	}
}

int main()
{
	std::cout << "Hello World!\n";
	Graph graph = Graph();
	graph.generateGraph(15, 20, 1);
	graph.print();
	approximativeResolution(graph);
	graph.printAdjacencyMatrix();
}
