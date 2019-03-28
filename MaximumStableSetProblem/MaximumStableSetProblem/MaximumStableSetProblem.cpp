#include "pch.h"
#include <iostream>
#include "Graph.h"
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;


//*Signatures des methodes de resolution
enum GraphMethods {Approchee, Exacte, MatriceAdjacence};

void approximativeResolution(Graph graph);
void exactResolution(Graph graph);

//*Signature des methodes calcul du temps d'execution
void CalculateTime(Graph *graph, GraphMethods method);
void GraphMethodCall(Graph *g, GraphMethods method);


int main()
{
	std::cout << "---Hello World!--- \n";

	
	Graph graph = Graph();
	graph.generateGraph(10, 2, 40);
	graph.print();

	CalculateTime( &graph, MatriceAdjacence);

	graph.printAdjacencyMatrix();
	//approximativeResolution(graph);

	return 0;
}



#pragma region TimeControl 
//*Calcule le temps d'execution d'une fonction d'un graphe (Choisir via Graph method)*//
void CalculateTime(Graph *graph, GraphMethods method) {

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	GraphMethodCall(graph, method);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "execution time : " << duration << " micro seconds" << endl;
}

//* Quelle méthode et comment est-elle appelée en fonction du nom (enum GraphMethods) *//
void GraphMethodCall(Graph *g, GraphMethods method)
{
	switch (method)
	{
	case Approchee:
		exactResolution(*g);
		break;
	case Exacte:
		approximativeResolution(*g);
		break;
	case MatriceAdjacence:
		g->generateAdjacencyMatrix();
		break;
	default:
		cout << "---No method indicated---" << endl;
		break;
	}
}
#pragma endregion

#pragma region Resolution
void approximativeResolution(Graph graph)
{
	std::vector<Vertex> mwis = graph.revolveMaximumIndependentSet();
	for (int i = 0; i < mwis.size(); i++)
	{
		std::cout << "index:" << mwis[i].getIndex() << "\n";
	}
}

void exactResolution(Graph graph)
{
	cout << "---A faire---" << endl;
}
#pragma endregion

