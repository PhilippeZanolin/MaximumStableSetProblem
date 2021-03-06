#include "pch.h"
#include <iostream>
#include "Graph.h"
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;
using namespace std::chrono;

std::mutex mtx;

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
	thread t;
	vector<thread> threads;
	//create threads
	for (int i = 0; i < 10; ++i)
	{
		graph = Graph(i);
		graph.generateGraph(5, 25, i);
		threads.emplace_back(thread(&resolve, graph));
	}
	//wait for them to complete
	for (auto& th : threads)
		th.join();
}
void resolve(Graph graph)
{
	long long time1 = CalculateTime(&graph, Approchee);
	long long time2 = CalculateTime(&graph, Exacte);
}
///Implementations///
#pragma region TimeControl 
//*Calcule le temps d'execution d'une fonction d'un graphe (Choisir via Graph method)*//
long long CalculateTime(Graph *graph, GraphMethods method) {
	mtx.lock();
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	GraphMethodCall(graph, method);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "------------" << endl;
	cout << "execution time methode " << (method == 0 ? "approchee" : "exacte") << " : " << duration << " micro seconds" << endl;
	mtx.unlock();
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
	//graph.print();
	cout << "Graph approche n :" << graph.getIndex() << endl;
	cout << "validity : " << (graph.isValid(mwis) ? "true" : "false") << endl;
	cout << "Cardinalite : " << mwis.size() << endl;
	printSolution(mwis);
}

void exactResolution(Graph graph)
{
	vector<Vertex> sol = Graph::resolveMaximumIndependentSetExact(graph, vector<Vertex>()); //pour resoudre on envoie le graph et un ensemble vide pour remplir la solution
	//graph.print();
	cout << "Graph exact n :" << graph.getIndex() << endl;
	cout << "Cardinalite : " << sol.size() << endl;
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