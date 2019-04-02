#include "pch.h"
#include "Graph.h"
#include <time.h> 

using namespace std;

Graph::Graph()
{
}
Graph::Graph(int index)
{
	this->index = index;
}
Graph::~Graph()
{
	int i;
	for (i = 0; i < vertices.size(); i++) 
	{
		adjacencyMatrix[i] = nullptr;
		delete(adjacencyMatrix[i]);
	}
	adjacencyMatrix = nullptr;
}
void Graph::addVertex(Vertex vertex)
{
	vertices.push_back(vertex);
}
void Graph::RemoveVertex(Vertex* vertex)
{
	int i;
	for (i = 0; i < vertices.size(); i++) {
		for (int j = 0; j < vertices[i].getNeighbors().size(); j++)
		{
			vector<Vertex> neighbors = vertices[i].getNeighbors();
			if (*vertex == neighbors[j])
				neighbors.erase(neighbors.begin() + j);
		}
	}
	for (i = 0; i < vertices.size(); i++) {
		if (vertices[i] == *vertex)
		{
			vertices.erase(vertices.begin() + i);
		}
	}
	
}
void Graph::RemoveVertex(int index)
{
	int i;
	vector<Vertex> neighbors;
	for (i = 0; i < vertices.size(); i++) {
		for (int j = 0; j < vertices[i].getNeighbors().size(); j++)
		{
			neighbors = vertices[i].getNeighbors();
			if (index == neighbors[j].getIndex())
				(vertices[i].neighbors).erase((vertices[i].neighbors).begin() + j);
		}
	}
	for (i = 0; i < vertices.size(); i++) {
		if (vertices[i].getIndex() == index)
		{
			vertices.erase(vertices.begin() + i);
		}
	}

}
bool Graph::addEdge(Vertex *vertex1, Vertex *vertex2)
{
	Edge newEdge = Edge(*vertex1, *vertex2);
	if (exists(newEdge))
		return false;
	vertex1->addNeighbor(*vertex2);
	vertex2->addNeighbor(*vertex1);
	edges.emplace_back(newEdge);
	return true;
}
bool Graph::addEdge(Vertex* vertex1, Vertex* vertex2, double probability)
{
	Edge newEdge = Edge(*vertex1, *vertex2);
	if (exists(newEdge))
		return false;
	double random = rand() % 100 + 1;
	if (random <= probability)
	{
		vertex1->addNeighbor(*vertex2);
		vertex2->addNeighbor(*vertex1);
		edges.emplace_back(newEdge);
		return true;
	}
	return false;
}
bool Graph::exists(Edge edge)
{
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i] == edge)
			return true;
	}
	return false;
}
bool Graph::isValid(vector<Vertex> solution)
{
	for (int i = 0; i < solution.size() - 1; i++)
	{
		for (int j = i+1; j < solution.size(); j++)
		{
			if (exists(Edge(solution[i], solution[j])))
				return false;

		}
	}
	return true;
}
void Graph::print()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		cout << "Sommet numero " << vertices[i].getIndex() << " du graphe" << endl;
	}
	for (int i = 0; i < edges.size(); i++)
	{
		cout << "Pont entre les sommets " << edges[i].getVertices()[0].getIndex() << " et " << edges[i].getVertices()[1].getIndex() << endl;
	}
}
void Graph::generateGraph(int n, int p, int index)
{
	srand(index);
	double weight;
	Vertex newVertex;
	for (int i = 0; i < n; i++)
	{
		weight = 1;
		newVertex = Vertex(i, weight);
		vertices.emplace_back(newVertex);
	}
	for (int i = 0; i < vertices.size() - 1; i++)
	{
		for (int j = i + 1; j < vertices.size(); j++)
		{
			addEdge(&vertices[i], &vertices[j], p);
		}
	}
	adjacencyMatrix = new int*[vertices.size()];
	for (int i = 0; i < vertices.size(); i++)
	{
		adjacencyMatrix[i]=  new int[vertices.size()];
	}
}
void Graph::generateAdjacencyMatrix(vector<Vertex> verticesCopy)
{
	int index;
	for (int i = 0; i < verticesCopy.size(); i++)
	{
		for (int k = 0; k < verticesCopy.size(); k++)
		{
			adjacencyMatrix[i][k] = 0;
		}
		for (int j = 0; j < verticesCopy[i].getNeighbors().size(); j++)
		{
			index = verticesCopy[i].getNeighbors()[j].getIndex();
			adjacencyMatrix[i][index] = 1;
		}
	}
}
void Graph::printAdjacencyMatrix()
{
	cout << "---Adjency matrix---" << endl;
	for (int i = 0; i < vertices.size(); i++)
	{
		for (int j = 0; j < vertices.size(); j++)
		{
			cout << adjacencyMatrix[i][j];
		}
		cout << endl;
	}
}
vector<Vertex> Graph::resolveMaximumIndependentSetApproched()
{
	vector<Vertex> mwis = vector<Vertex>();// Maximum Weighted Independent Stable
	vector<Vertex> mwvc = vector<Vertex>(); // Maximum Weighted Vectex Cover
	// On effectue une copie de la liste de sommets du graphe afin de ne pas la modifier
	// Pour l'utiliser plus tard avec la méthode de résolution exacte
	vector<Vertex> verticesCopy; 
	for (int i = 0; i < vertices.size(); i++)
		verticesCopy.emplace_back(vertices[i]);
	generateAdjacencyMatrix(verticesCopy);
	int ** adjacencyCopy;
	adjacencyCopy = new int*[verticesCopy.size()];
	for (int i = 0; i < verticesCopy.size(); i++)
	{
		adjacencyCopy[i] = new int[verticesCopy.size()];
	}
	for (int i = 0; i < verticesCopy.size(); i++)
	{
		for (int j = 0; j < verticesCopy.size(); j++)
		{
			adjacencyCopy[i][j] = adjacencyMatrix[i][j];
		}
	}
	int max;
	// On cherche la couverture minimum du graphe
	// On répète l'opération tant que la matrice d'adjacence n'est pas vide
	while (!adjacencyMatrixIsEmpty(adjacencyCopy, verticesCopy))
	{
		// On récupère à chaque fois le sommet au ratio le plus élevé, qu'on ajoute a la couverture minimum
		max = indexMaxRatio(verticesCopy);
		mwvc.emplace_back(verticesCopy[max]);
		// On supprime le sommet ajouté à la couverture minimum de la liste de sommets du graphe
		verticesCopy.erase(verticesCopy.begin() + max); 
		for (int i = 0; i < verticesCopy.size(); i++)
		{
			// On met a jour la matrice d'adjacence en en retirant le sommet
			// qu'on vient d'ajouter à la couverture minimum
			adjacencyCopy[max][i] = 0;
			adjacencyCopy[i][max] = 0;
		}
	}
	bool isInVertexCover = false;
	// On ajoute au stable tous les sommets n'étant pas
	// inclus dans la couverture minimum du graphe
	for (int i = 0; i < verticesCopy.size(); i++)
	{
		for(int j=0; j < mwvc.size(); j++)
		{
			if(mwvc[j] == verticesCopy[i])
				isInVertexCover = true;
		}
		if (!isInVertexCover)
			mwis.emplace_back(verticesCopy[i]);
		isInVertexCover = false;
	}
	return mwis;
}

std::vector<Vertex> Graph::resolveMaximumIndependentSetExact(Graph graph, std::vector<Vertex> currentSet)
{
	//On regarde si le graphe courant possède des sommets
	if (!graph.isEmpty())
	{
		//On initialise le set maximal a vide
		vector<Vertex> maxSet = vector<Vertex>();

		//On va parcourir tous les sommets du graphe
		int index;
		for (index = 0; index < graph.vertices.size(); index++)
		{
			//Copie du sous graphe actuel 
			Graph subGraph = Graph(graph);
			
			Vertex currentVertex = graph.vertices[index];
			int neigIndx;

			//On doit retirer au nouveau graphe tous les voisins du sommets
			for (neigIndx = 0; neigIndx < currentVertex.getNeighbors().size(); neigIndx++)
			{
				subGraph.RemoveVertex(currentVertex.getNeighbors()[neigIndx].getIndex());
			}

			//On ajoute au set le sommet
			vector<Vertex> currentSetCopy = vector<Vertex>(currentSet);
			currentSetCopy.push_back(currentVertex);
			//on supprime le sommet
			subGraph.RemoveVertex(currentVertex.getIndex());
			//on rappel la fonction avec le nouveau graphe
			vector<Vertex> tempSet = resolveMaximumIndependentSetExact(subGraph, currentSetCopy);

			//On compare la cardinalite des 2 sets pour garder le maxium
			if (tempSet.size() > maxSet.size())
			{
				maxSet = tempSet;
			}
		}

		return maxSet;
	}
	else
	{
		return currentSet;
	}
}
bool Graph::adjacencyMatrixIsEmpty(int ** adjacencyCopy, vector<Vertex> verticesCopy)
{
	for (int i = 0; i < verticesCopy.size(); i++)
	{
		for (int j = 0; j < verticesCopy.size(); j++)
		{
			if (adjacencyCopy[i][j] == 1)
				return false;
		}
	}
	return true;
}
int Graph::indexMaxRatio(vector<Vertex> verticesCopy)
{
	int indexMax = 0;
	int ratio = verticesCopy[0].getRatio();
	for (int i = 1; i < verticesCopy.size(); i++)
	{
		if (ratio < verticesCopy[i].getRatio())
		{
			indexMax = i;
			ratio = verticesCopy[i].getRatio();
		}
	}
	return indexMax;
}
int Graph::getIndex(int index, Graph graph)
{
	int indexVertex = -1;
	for (int i = 0; i < graph.vertices.size(); i++)
		if (vertices[i].getIndex() == index)
			indexVertex = i;
	return indexVertex;
}
Vertex Graph::getMinimalDegreeVertex()
{
	if (vertices.size() == 0) 
	{
		return Vertex();
	}
	Vertex minD = vertices[0];
	int i;
	for (i = 1; i < vertices.size(); i++) 
	{
		if (vertices[i].getDegree() < minD.getDegree()) {
			minD = vertices[i];
		}
	}
	return minD;
}
int Graph::getMinimalDegreeIndex()
{
	if (vertices.size() == 0)
	{
		return -1;
	}
	int minD = 0;
	int i;
	for (i = 1; i < vertices.size(); i++)
	{
		if (vertices[i].getDegree() < vertices[minD].getDegree()) {
			minD = i;
		}
	}
	return minD;
}

