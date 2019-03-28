#include "pch.h"
#include "Graph.h"

using namespace std;

Graph::Graph()
{
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
void Graph::RemoveVertex(Vertex vertex)
{
	int i;
	for (i = 0; i < vertices.size(); i++) {
		if (vertices[i] == vertex) 
		{
			vertices.erase(vertices.begin() + i);
			return;
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
void Graph::generateGraph(int n, int p, int rangeWeight)
{
	double weight;
	Vertex newVertex;
	for (int i = 0; i < n; i++)
	{
		weight = rand() % rangeWeight + 1;
		newVertex = Vertex(i, weight);
		vertices.emplace_back(newVertex);
	}
	for (int i = 0; i < vertices.size() - 1; i++)
	{
		for (int j = i + 1; j < vertices.size(); j++)
		{
			addEdge(&vertices[i], &vertices[j], 50);
		}
	}
	adjacencyMatrix = new int*[vertices.size()];
	for (int i = 0; i < vertices.size(); i++)
	{
		adjacencyMatrix[i]=  new int[vertices.size()];
	}
}
void Graph::generateAdjacencyMatrix()
{
	int index;
	for (int i = 0; i < vertices.size(); i++)
	{
		for (int k = 0; k < vertices.size(); k++)
		{
			adjacencyMatrix[i][k] = 0;
		}
		for (int j = 0; j < vertices[i].getNeighbors().size(); j++)
		{
			index = vertices[i].getNeighbors()[j].getIndex();
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
vector<Vertex> Graph::revolveMaximumIndependentSetApproched()
{
	vector<Vertex> mwis = vector<Vertex>();
	vector<Vertex> mwvc = vector<Vertex>();
	generateAdjacencyMatrix();
	int t;
	int k = 0;
	double max;
	while (!adjacencyMatrixIsEmpty())
	{
		max = vertices[0].getRatio();
		for (int i = 1; i < vertices.size(); i++)
		{
			if (max < vertices[i].getRatio())
			{
				max = vertices[i].getRatio();
				t = i;
				mwvc.emplace_back(vertices[i]);
			}
			if (max == vertices[i].getRatio() && vertices[i - k].getSupport() <= vertices[i].getSupport())
			{
				max = vertices[i - k].getRatio();
				t = i - k;
				mwvc.emplace_back(vertices[i - k]);
			}
			k++;
		}
		for (int i = 0; i < vertices.size(); i++)
		{
			adjacencyMatrix[t][i] = 0;
			adjacencyMatrix[i][t] = 0;
		}

	}
	bool isInVertexCover = false;
	for (int i = 0; i < vertices.size(); i++)
	{
		for(int j=0; j < mwvc.size(); j++)
		{
			if(mwvc[i] == vertices[0])
				isInVertexCover = true;
		}
		if (!isInVertexCover)
			mwis.emplace_back(vertices[i]);
		isInVertexCover = false;
	}
	return mwis;
}

std::vector<Vertex> Graph::revolveMaximumIndependentSetExact(Graph graph, std::vector<Vertex> currentSet)
{

	//On regarde si le graphe courant possède des sommets
	if (!graph.isEmpty())
	{
		//On recupère le vertex de degree minimal
		Vertex v = graph.getMinimalDegreeVertex();

		//On initialise le set maximal a vide
		vector<Vertex> maxSet = vector<Vertex>();

		//On va parcourir tous les voisins du vertex du plus petit degré
		int index;
		for (index = 0; index < v.getNeighbors().size(); index++)
		{

			//Copie du sous graphe actuel 
			Graph subGraph = Graph(graph);

			//On doit retirer au nouveau graphe tous les voisins du voisin (propagation de l'aglo)
			Vertex voisin = v.getNeighbors()[index];

			int neigIndx;
			for (neigIndx = 0; neigIndx < voisin.getNeighbors().size(); neigIndx++)
			{
				subGraph.RemoveVertex(voisin.getNeighbors()[neigIndx]);
			}

			//On ajoute au set le voisin
			currentSet.push_back(voisin);
			vector<Vertex> tempSet = revolveMaximumIndependentSetExact(subGraph, currentSet);

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
bool Graph::adjacencyMatrixIsEmpty()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		for (int j = 0; j < vertices.size(); j++)
		{
			if (adjacencyMatrix[i][j] == 1)
				return false;
		}
	}
	return true;
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


