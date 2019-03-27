#include "pch.h"
#include "Graph.h"


using namespace std;

Graph::Graph()
{
}
Graph::~Graph()
{
}
void Graph::addVertex(Vertex vertex)
{
	vertices.push_back(vertex);
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
	for (int i = 0; i < vertices.size(); i++)
	{
		for (int j = 0; j < vertices.size(); j++)
		{
			cout << adjacencyMatrix[i][j];
		}
		cout << endl;
	}
}
/*vector<Vertex> Graph::revolveMaximumIndependentSet()
{
	vector<Vertex> mwis = vector<Vertex>();
	vector<Vertex> mwvc = vector<Vertex>();
	generateAdjacencyMatrix();
	int d;
	while (edges.size() != 0)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			for (int j = 0; j < vertices.size(); j++)
			{
				d = 0;
			}
		}
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		if (mwvc.find(vertices[i]) == mwvc.end())
			mwis.emplace_back(vertices[i]);
	}
	return mwis;
}*/