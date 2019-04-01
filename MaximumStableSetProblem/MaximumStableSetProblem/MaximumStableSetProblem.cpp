#include "pch.h"
#include <iostream>
#include "Graph.h"
#include <chrono>
#include <thread>
#include <future>

using namespace std;
using namespace std::chrono;

///Declaration des fonctions. implementation apres le main///
//*Signatures des methodes de resolution (est-ce qu'on affiche juste le résultat, ou sauvergarde dans un fichier etc.. à faire dans ces fonctions)
enum GraphMethods { Approchee, Exacte };

void approximativeResolution(Graph graph);
void exactResolution(Graph graph);
void resolve(Graph graph);

//*Signature des methodes calcul du temps d'execution
long long CalculateTime(Graph *graph, GraphMethods method);
void GraphMethodCall(Graph *g, GraphMethods method);

//*Affichage
void printSolution(vector<Vertex> sol);

///Main///
int main()
{
	std::cout << "Hello World!\n";
	Graph graph;
	for (int i = 0; i < 1; i++)
	{
		graph = Graph();
		graph.generateGraph(15, 10, 1);
		graph.print();
		thread t = thread(&resolve, graph);
		t.join();
		//resolve(graph, Approchee);
		//resolve(graph, Exacte);
	}
}
void resolve(Graph graph)
{
	long long time1 = CalculateTime(&graph, Approchee);
	cout << "------------" << endl;
	cout << "execution time methode approchee : " << time1 << " micro seconds" << endl;
	long long time2 = CalculateTime(&graph, Exacte);
	cout << "------------" << endl;
	cout << "execution time methode exacte : " << time2 << " micro seconds" << endl;
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
		approximativeResolution(*g);
		break;
	case Exacte:
		exactResolution(*g);
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
	std::vector<Vertex> mwis = graph.resolveMaximumIndependentSetApproched();
	printSolution(mwis);
}

void exactResolution(Graph graph)
{
	vector<Vertex> sol = Graph::resolveMaximumIndependentSetExact(graph, vector<Vertex>()); //pour resoudre on envoie le graph et un ensemble vide pour remplir la solution
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