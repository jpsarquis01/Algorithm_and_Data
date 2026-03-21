#pragma once

#include "Vector.h"
#include "PriorityQueue.h"
#include <queue>

template <typename T, typename W = int>
class MSTGraph
{
public:
	struct Edge
	{
		int fromIndex = -1;
		int toIndex = -1;
		W weight;

		bool operator<(const Edge& rhs) const { return weight < rhs.weight; }
		bool operator<=(const Edge& rhs) const { return weight <= rhs.weight; }
		bool operator==(const Edge& rhs) const { return weight == rhs.weight; }
		bool operator>(const Edge& rhs) const { return weight > rhs.weight; }
		bool operator>=(const Edge& rhs) const { return weight >= rhs.weight; }
	};
	struct Node
	{
		const T* data = nullptr;
		bool isVisited = false;
		bool addedToProcess = false;
		W bestWeight;
		Vector<Edge> edges;
	};
public:
	MSTGraph()
	{

	}
	~MSTGraph()
	{
		Terminate();
	}

	void AddItem(const T* data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		newNode->isVisited = false;
		mNodes.PushBack(newNode);
	}

	void AddEdge(int a, int b, W weight, bool bothWays = false)
	{
		if (a < 0 || b < 0 || a >= mNodes.Size() || b >= mNodes.Size())
		{
			return;
		}
		Edge edgeA = { a, b, weight };
		mNodes[a]->edges.PushBack(edgeA);
		if (bothWays)
		{
			Edge edgeB = { b, a, weight };
			mNodes[b]->edges.PushBack(edgeB);
		}
	}

	void GenerateMST(int startNode)
	{
		// going to use Prism Algorithm 
		Reset();

		// use the std version so that we can use a different compare function
		Vector<T> nodeWeights;
		nodeWeights.Resize(mNodes.Size());
		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> process;
		process.push({ -1, startNode, 0 });
		while (!process.empty())
		{
			Edge edge = process.top();
			process.pop();
			Node* node = mNodes[edge.toIndex];
			if (!node->isVisited)
			{
				node->isVisited = true;
				if (edge.fromIndex != -1)
				{
					mMSTGraph.PushBack(edge);
				}
				for (std::size_t i = 0; i < node->edges.Size(); ++i)
				{
					const Edge& edge = node->edges[i];
					Node* toNode = mNodes[edge.toIndex];
					if (!toNode->isVisited && (!toNode->addedToProcess || edge.weight < toNode->bestWeight))
					{
						toNode->addedToProcess = true;
						toNode->bestWeight = edge.weight;
						process.push(edge);
					}
				}
			}
		}
	}

	const Vector<Edge>& GetMST() const
	{
		return mMSTGraph;
	}

	void Terminate()
	{
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			delete mNodes[i];
			mNodes[i] = nullptr;
		}
		mNodes.Clear();
	}
private:
	void Reset()
	{
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			mNodes[i]->isVisited = false;
			mNodes[i]->addedToProcess = false;
		}
	}
	Vector<Node*> mNodes;
	Vector<Edge> mMSTGraph;
};