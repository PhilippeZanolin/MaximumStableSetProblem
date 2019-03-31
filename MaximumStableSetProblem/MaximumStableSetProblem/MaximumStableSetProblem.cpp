#include "pch.h"
#include <iostream>
#include "Graph.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

///Declaration des fonctions. implementation apres le main///
//*Signatures des methodes de resolution (est-ce qu'on affiche juste le résultat, ou sauvergarde dans un fichier etc.. à faire dans ces fonctions)
enum GraphMethods { Approchee, Exacte, MatriceAdjacence };

void approximativeResolution(Graph graph);
void exactResolution(Graph graph);

//*Signature des methodes calcul du temps d'execution
long long CalculateTime(Graph *graph, GraphMethods method);
void GraphMethodCall(Graph *g, GraphMethods method);

//*Affichage
void printSolution(vector<Vertex> sol);

///Main///
int main()
{
	std::cout << "Hello World!\n";
	Graph graph = Graph();
	graph.generateGraph(30, 20, 1);
	graph.print();
	long long time = CalculateTime(&graph, MatriceAdjacence);
	approximativeResolution(graph);
	cout << "------------" << endl;
	cout << "execution time : " << time << " micro seconds" << endl;
}

///Implementations///
#pragma region TimeControl 
//*Calcule le temps d'execution d'une fonction d'un graphe (Choisir via Graph method)*//
long long CalculateTime(Graph *graph, GraphMethods method) {

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	GraphMethodCall(graph, method);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2 - t1).count();

	//cout << "execution time : " << duration << " micro seconds" << endl;

	return duration;
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
	std::vector<Vertex> mwis = graph.revolveMaximumIndependentSetApproched();
	printSolution(mwis);
}

void exactResolution(Graph graph)
{
	vector<Vertex> sol = Graph::revolveMaximumIndependentSetExact(graph, vector<Vertex>()); //pour resoudre on envoie le graph et un ensemble vide pour remplir la solution
	printSolution(sol);
}

void printSolution(vector<Vertex> sol)
{
	for (int i = 0; i < sol.size(); i++)
	{
		std::cout << "index:" << sol[i].getIndex() << "\n";
	}
}
#pragma endregion