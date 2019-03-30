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
			addEdge(&vertices[i], &vertices[j], p);
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
vector<Vertex> Graph::revolveMaximumIndependentSet()
{
	vector<Vertex> mwis = vector<Vertex>();
	vector<Vertex> mwvc = vector<Vertex>();
	generateAdjacencyMatrix();
	printAdjacencyMatrix();
	int max;
	while (!adjacencyMatrixIsEmpty())
	{
		max = indexMaxRatio();
		mwvc.emplace_back(vertices[max]);
		vertices.erase(vertices.begin() + max);
		for (int i = 0; i < vertices.size(); i++)
		{
			adjacencyMatrix[max][i] = 0;
			adjacencyMatrix[i][max] = 0;
		}
	}
	bool isInVertexCover = false;
	for (int i = 0; i < vertices.size(); i++)
	{
		for(int j=0; j < mwvc.size(); j++)
		{
			if(mwvc[j] == vertices[i])
				isInVertexCover = true;
		}
		if (!isInVertexCover)
			mwis.emplace_back(vertices[i]);
		isInVertexCover = false;
	}
	return mwis;
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
int Graph::indexMaxRatio()
{
	int indexMax = 0;
	int ratio = vertices[0].getRatio();
	for (int i = 1; i < vertices.size(); i++)
	{
		if (ratio < vertices[i].getRatio())
		{
			indexMax = i;
			ratio = vertices[i].getRatio();
		}
	}
	return indexMax;
}
